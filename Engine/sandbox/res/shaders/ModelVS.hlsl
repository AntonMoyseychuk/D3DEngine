struct VS_INPUT
{
    float3 Position : POSITION;
    float2 Texture : TEXCOORD0;
    float3 Normal : NORMAL;
};

struct VS_OUT
{
	float4 Position : SV_POSITION;
	float2 Texture : TEXCOORD0;
    float3 Normal : TEXCOORD1;
};

cbuffer Matrixes
{
    matrix Model;
    matrix View;
    matrix Proj;
};

VS_OUT main(VS_INPUT input)
{
    VS_OUT output;
    output.Position = mul(float4(input.Position, 1.0f), Model);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Proj);
    
    output.Normal = mul(input.Normal, (float3x3)Model);
    
    output.Texture = input.Texture;

    return output;
}