#ifndef _TileAnimFX
#define _TileAnimFX

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

VS_OUT VS_TileAnimFX(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;

    output.vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);

    return output;
}

float4 PS_TileAnimFX(VS_OUT _in) : SV_Target
{
    //에니메이션이 없을땐 0으로 해서 안보이도록
    float4 vColor = float4(0.f, 0.f, 0.f, 0.f);

    if (g_UseAnim2D)
    {
        
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
        }
    }
        
    // 광원 처리
    // 광원의 타입별 처리
    // 광원이 여러개일 때 처리
    //g_Light2DCount;    
    tLightColor LightColor = (tLightColor) 0.f;
    
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        CalLight2D(_in.vWorldPos, i, LightColor);
    }
    
    vColor.rgb *= (LightColor.vColor.rgb + LightColor.vAmbient.rgb);
        
    if (0.f == vColor.a)
        discard;
    
    float x = g_NoiseTex.Sample(g_sam_0, _in.vUV).x;
    if (0 > x - g_float_1)
    {
        discard;
    }
    
    return vColor;
}
#endif