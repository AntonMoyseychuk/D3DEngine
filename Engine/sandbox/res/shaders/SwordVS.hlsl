struct VSOut
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

cbuffer ConstantBuffer
{
    matrix Model;
    matrix View;
    matrix Proj;
};

VSOut main(float3 Pos : POSITION, float4 Color : COLOR)
{
    VSOut output;
    output.Pos = mul(float4(Pos, 1.0f), Model);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Proj);
    output.Color = Color;

    return output;
}