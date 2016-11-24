
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
    DirectionalLight light;
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




float4 pMain(VertexOut pIn) : SV_TARGET
{

	float4 color = pIn.Color;


    return color;

}

