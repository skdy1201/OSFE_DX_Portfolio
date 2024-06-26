#ifndef _ChangeRed
#define _ChangeRed

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

VS_OUT VS_ChangeRed(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    output.vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    
    return output;
}

float4 PS_ChangeRed(VS_OUT _in) : SV_Target
{
    float4 vColor = float4(1.f, 0.f, 1.f, 0.f);
    

    if (g_UseAnim2D)
    {
        vColor.a = 1.f;
       


        float2 vBackgroundLeftTop = g_vLeftTop + (g_vSlizeSize / 2.f) - (g_vBackground / 2.f);
        vBackgroundLeftTop -= g_vOffset;
        float2 vUV = vBackgroundLeftTop + (g_vBackground * _in.vUV);
        
        if (vUV.x < g_vLeftTop.x || (g_vLeftTop.x + g_vSlizeSize.x) < vUV.x
            || vUV.y < g_vLeftTop.y || (g_vLeftTop.y + g_vSlizeSize.y) < vUV.y)
        {
            //vColor = float4(1.f, 1.f, 0.f, 1.f);
            discard;
        }
        else
        {
            vColor = g_anim2d_tex.Sample(g_sam_1, vUV);
            //vColor.g = 0.0f; // 녹색 성분 제거
            //vColor.b = 0.0f; // 파란색 성분 제거

        }
    }


    vColor.r = 1.f;
    vColor.g = 0.f;
    vColor.b = 0.f;

    if (vColor.a < 0.1f)
        discard;



    return vColor;
}
#endif
