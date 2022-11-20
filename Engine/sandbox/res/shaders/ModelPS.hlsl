Texture2D Texture : register(t0);   
SamplerState TextureSample : register(s0);

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float2 Texture : TEXCOORD0;
    float3 Normal : TEXCOORD1;
};

cbuffer Light
{
    float4 LightPosition;
    float4 LightColor;
    
    float4 CameraPosition;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    //AMBIENT LIGHT
    float ka = 0.1f;
    float3 ia = LightColor.rgb;
    float3 ambientLight = ka * ia;
    
    //DIFFUSED LIGHT
    float kd = 0.9f;
    float id = LightColor.rgb;
    float3 lightDir = normalize(LightPosition.xyz - input.Position.xyz);
    float amountDiffusedLight = max(0.0f, dot(input.Normal, lightDir));
    float3 diffusedLight = kd * amountDiffusedLight * id;
    
    //SPECULAR LIGHT
    float ks = 1.0f;
    float is = LightColor.rgb;
    float3 reflectedLight = reflect(-lightDir, input.Normal);
    float3 cameraDir = normalize(CameraPosition.xyz - input.Position.xyz);
    float amountSpecularLight = pow(max(0.0f, dot(cameraDir, reflectedLight)), 250.0f);
    float3 specularLight = ks * amountSpecularLight * is;
    
    float3 finalColor = ambientLight + diffusedLight + specularLight;
    
    return Texture.Sample(TextureSample, input.Texture) * float4(finalColor, 1.0f);
}