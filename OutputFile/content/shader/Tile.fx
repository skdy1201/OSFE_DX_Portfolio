#ifndef _TileFX
#define _TileFX

#include "value.fx"
#include "func.fx"



struct VS_IN
{
    float4 vColor : COLOR;
    float3 vPos : POSITION; // Sementic
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
    
    float3 vWorldPos : POSITION;
};

VS_OUT VS_TileFX(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;

    output.vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);

    return output;
}

float4 PS_TileFX(VS_OUT _in) : SV_Target
{


    float4 vOutColor = float4(1.f, 0.f, 1.f, 1.f);
   
    if(g_int_0 == 1 )
    vOutColor = g_tex_0.Sample(g_sam_1, _in.vUV);
    else
        vOutColor = g_tex_1.Sample(g_sam_1, _in.vUV);
    // 알파값이 0인 부분은 discard
    //if (0.f >= vOutColor.a)
    //    discard;
    
    // Vec4파라미터로 전달된 색상으로 변경하기
    // 우선 테스트용으로 Alpha값을 제외한 나머지 RGB색상만 변경해보기
    vOutColor.x *= g_vec4_0.x;
    vOutColor.y *= g_vec4_0.y;
    vOutColor.z *= g_vec4_0.z;
    vOutColor.w *= g_vec4_0.w;
    
    return vOutColor;

}

#endif