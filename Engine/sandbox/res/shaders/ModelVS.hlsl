struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

cbuffer ConstantBuffer
{
    matrix Model;
    matrix View;
    matrix Proj;
};

VS_OUT main(float3 Pos : POSITION, float2 Tex : TEXCOORD)
{
    VS_OUT output;
    output.Pos = mul(float4(Pos, 1.0f), Model);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Proj);
    output.Tex = Tex;

    return output;
}