Texture2D Texture : register(t0);
SamplerState TextureSample : register(s0);

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float2 Texture : TEXCOORD0;
    float3 Normal : TEXCOORD1;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    return Texture.Sample(TextureSample, input.Texture);
}