

cbuffer ModelViewProjectionConstantBuffer : register(b0) {
	matrix mWorld;       // world matrix for object
	matrix View;        // view matrix
	matrix Projection;  // projection matrix
	float gTime;
	float3 pad;
};




void vMain(float3 iPosL : POSITION,float4 iColor : COLOR, out float4 oPosH : SV_POSITION, out float4 oColor : COLOR) {
	

	float4 pos = float4(iPosL, 1.0f);

	//pos.xy += 0.5f*sin(pos.x)*sin(3.0f*gTime);
	//pos.z *= 0.6f + 0.4f*sin(2.0f*gTime);

	// Transform the position from object space to homogeneous projection space
	pos = mul(pos, mWorld);
	pos = mul(pos, View);
	pos = mul(pos, Projection);
	oPosH = pos;

	// Just pass through the color data
	oColor = iColor;

}

float4 pMain(float4 posH : SV_POSITION, float4 color : COLOR) : SV_Target
{
	return color;
}