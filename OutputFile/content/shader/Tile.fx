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
    float4 vColor;

    if (g_int_0)
    {
        vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
                    
            //saturate 0 ~ 1 �� ���� �ʰ� ����
        float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f);
        
        if (fAlpha < 0.1f)
        {
            // �ȼ� ���̴��� �߰��� ���ó��
            discard; //clip(-1);            
        }
    }

    if (g_int_1)
    {
        vColor = g_tex_1.Sample(g_sam_1, _in.vUV);
                    
            //saturate 0 ~ 1 �� ���� �ʰ� ����
        float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f);
        
        if (fAlpha < 0.1f)
        {
            // �ȼ� ���̴��� �߰��� ���ó��
            discard; //clip(-1);            
        }
    }

    if (g_int_2)
    {
        vColor = g_tex_2.Sample(g_sam_1, _in.vUV);
                    
            //saturate 0 ~ 1 �� ���� �ʰ� ����
        float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f);
        
        if (fAlpha < 0.1f)
        {
            // �ȼ� ���̴��� �߰��� ���ó��
            discard; //clip(-1);            
        }
    }


    tLightColor LightColor = (tLightColor) 0.f;
    
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        CalLight2D(_in.vWorldPos, i, LightColor);
    }
    
    vColor.rgb *= (LightColor.vColor.rgb + LightColor.vAmbient.rgb);
        
    if (0.f == vColor.a)
        discard;

    
    return vColor;

}

#endif