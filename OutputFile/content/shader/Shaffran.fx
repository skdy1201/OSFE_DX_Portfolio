#ifndef ShaffranFX
#define ShaffranFX

#include "value.fx"
#include "func.fx"

#define inputColor g_vec4_0

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

VS_OUT VS_ShaffranFX(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    output.vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    
    return output;
}

float4 PS_ShaffranFX(VS_OUT _in) : SV_Target
{
    float4 vOutColor = float4(1.f, 0.f, 1.f, 1.f);


    //인호 코드
    //if (g_btex_0)
    //{
	   // vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
        
	   // float sum = vColor.r + vColor.g + vColor.b;

	   // if (sum < 2.8f)
	   // {
		  //  vColor.rgb += inputColor.rgb;
	   // }
    //}

    vOutColor = g_tex_0.Sample(g_sam_1, _in.vUV);

    // 부분이 나뉘어서 파라미터를 두개줌
    

    if ((vOutColor.r <= 1.f)
      && (vOutColor.g <= 1.f)
        && (vOutColor.b < 1.f))
    {
        if (vOutColor.b == 0.f)
        {
            vOutColor.rgb += g_vec4_0.rgb;
        }
        else
        {
            vOutColor.rgb *= g_vec4_1.rgb;
        }
    }


    if (0.01 > vOutColor.a)
    {
	    discard;
    }


    return vOutColor;

}


#endif