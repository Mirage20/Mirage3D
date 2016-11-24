
struct Material
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
};

struct DirectionalLight
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float3 Direction;
    float Pad;
};

cbuffer cbPerObject : register(b0)
{

	matrix mWorld; // world matrix for object
	matrix View; // view matrix
	matrix Projection; // projection matrix
	matrix gWorldInvTranspose;
	matrix gTexTransform;
    Material gMaterial;
};


cbuffer cbPerFrame : register(b1)
{
    DirectionalLight light[2];
	float3 eyePos;
	float gTime;
};

Texture2D gDiffuseMap : register(t0);

SamplerState samAnisotropic : register(s0);

struct VertexIn
{
	float3 PositionLocal : POSITION;
	float3 NormalLocal : NORMAL;
	float4 Color : COLOR;
	float2 Texture : TEXTURE;
};

struct VertexOut
{
	float4 PositionHomogeneous : SV_POSITION;
	float4 Color : COLOR;
	float3 PositionWorld : POSITION;
	float3 NormalWorld : NORMAL;
    float2 Texture : TEXTURE;
};


void vMain(VertexIn vIn, out VertexOut vOut) {
	

	float4 pos = float4(vIn.PositionLocal, 1.0f);

	//pos.xy += 0.5f*sin(pos.x)*sin(3.0f*gTime);
	//pos.z *= 0.6f + 0.4f*sin(2.0f*gTime);

	// Transform the position from object space to homogeneous projection space
	pos = mul(pos, mWorld);
	pos = mul(pos, View);
	pos = mul(pos, Projection);
	vOut.PositionHomogeneous = pos;

	// Transform vertex in to world space
	vOut.PositionWorld = mul(float4(vIn.PositionLocal, 1.0f), mWorld).xyz;

	// Transform normal vectors to world space
	vOut.NormalWorld = mul(vIn.NormalLocal, (float3x3) gWorldInvTranspose);

	// Transform textures to world space
	vOut.Texture = mul(float4(vIn.Texture, 0.0f, 1.0f), gTexTransform).xy;	

	// Pass vertex color data.
	vOut.Color = vIn.Color;

}


void ComputeDirectionalLight(
	Material material,
	DirectionalLight light,
	float3 normal, float3 toEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec) {

	// Initialize outputs.
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
	// The light vector aims opposite the direction the light rays travel.
    float3 lightVec = -light.Direction;
	// Add ambient term.
    ambient = material.Ambient * light.Ambient;
	// Add diffuse and specular term, provided the surface is in
	// the line of site of the light.
	float diffuseFactor = dot(lightVec, normal);
	// Flatten to avoid dynamic branching.

	if (diffuseFactor > 0.0f) {
		float3 v = reflect(-lightVec, normal);
        float specFactor = pow(max(dot(v, toEye), 0.0f), gMaterial.Specular.w);
        diffuse = diffuseFactor * material.Diffuse * light.Diffuse;
        spec = specFactor * material.Specular * light.Specular;
    }
}


float4 pMain(VertexOut pIn) : SV_TARGET
{

	// Interpolating normal can unnormalize it, so normalize it.
    pIn.NormalWorld = normalize(pIn.NormalWorld);
	
    float3 toEyeW = normalize(eyePos - pIn.PositionWorld);

	// Start with a sum of zero.
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
	// Sum the light contribution from each light source.
	float4 A, D, S;
    ComputeDirectionalLight(gMaterial, light[0], pIn.NormalWorld, toEyeW, A, D, S);
	
	ambient += A;
	diffuse += D;
	spec += S;
	float4 texColor = gDiffuseMap.Sample(samAnisotropic, pIn.Texture);

	//float4 litColor = ambient + diffuse + spec;
	float4 litColor = texColor*(ambient + diffuse) + spec;
	// Common to take alpha from diffuse material.
    litColor.a = gMaterial.Diffuse.a;
	return litColor;

	// Invert the light direction for calculations.
	//float3 lightDir = -Direction;

	// Calculate the amount of light on this pixel.
	//float lightIntensity = saturate(dot(NormalW, lightDir));



	//return saturate(Diffuse * lightIntensity);


	//return color;
}

