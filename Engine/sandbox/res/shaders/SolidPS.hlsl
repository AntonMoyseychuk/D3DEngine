cbuffer Color
{
    float4 Color;
};

float4 main() : SV_Target
{
    return Color;
}