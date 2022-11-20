cbuffer Matrixes
{
    matrix Model;
    matrix View;
    matrix Proj;
};

float4 main(float3 Pos : POSITION) : SV_Position
{
    float4 output = mul(float4(Pos, 1.0f), Model);
    output = mul(output, View);
    output = mul(output, Proj);
    return output;
}