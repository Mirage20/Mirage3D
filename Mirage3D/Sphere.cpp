//#include <DirectXMath.h>
#include "Sphere.h"



void Sphere::Setup() {

	MeshData meshData= CreateSphere(1.0f,40,40);
	SetMesh(meshData);

	Material mat;
	mat.Name = L"basic";
	mat.Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mat.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mat.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 32.0f);
	mat.TextureName = L"earth";
	SetMaterial(mat);
	SetPosition(-2.0f, 0.0f, 0.0f);
}

void Sphere::Update(float delta, float gameTime) {
	RotateY(-delta * 20);
}

MeshData Sphere::CreateSphere(float radius, int sliceCount, int stackCount) {

	MeshData data;
	Vertex north = { XMFLOAT3(0.0f, radius, 0.0f), XMFLOAT3(0.0f,1.0f, 0.0f), *(XMFLOAT4*)&Colors::Red , XMFLOAT2(0.0f,0.0f) };
	data.Vertices.push_back(north);
	float phiStep = XM_PI / stackCount;
	float thetaStep = 2.0f * XM_PI / sliceCount;

	for (int i = 1; i <= stackCount - 1; i++) {
		float phi = i*phiStep;
		for (int j = 0; j <= sliceCount; j++) {
			float theta = j*thetaStep;

			XMFLOAT3 vertexPosition = XMFLOAT3((radius*XMScalarSin(phi)*XMScalarCos(theta)), (radius*XMScalarCos(phi)), (radius* XMScalarSin(phi)*XMScalarSin(theta)));
			XMFLOAT3 vertexNormal;
			XMStoreFloat3(&vertexNormal, XMVector3Normalize(XMLoadFloat3(&vertexPosition)));
			Vertex vertex = { vertexPosition, vertexNormal, *(XMFLOAT4*)&Colors::Red , XMFLOAT2(-theta / (XM_PI * 2), phi / XM_PI) };

			data.Vertices.push_back(vertex);
		}
	}
	Vertex south = { XMFLOAT3(0.0f, -radius, 0.0f), XMFLOAT3(0.0f,-1.0f, 0.0f), *(XMFLOAT4*)&Colors::Red , XMFLOAT2(0.0f,1.0f) };
	data.Vertices.push_back(south);


	for (int i = 1; i <= sliceCount; i++) {
		data.Indices.push_back(0);
		data.Indices.push_back(i);
		data.Indices.push_back(i + 1);

	}
	int baseIndex = 1;
	int ringVertexCount = sliceCount + 1;
	for (int i = 0; i < stackCount - 2; i++) {
		for (int j = 0; j < sliceCount; j++) {
			data.Indices.push_back(baseIndex + i*ringVertexCount + j);
			data.Indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);
			data.Indices.push_back(baseIndex + i*ringVertexCount + j + 1);


			data.Indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);
			data.Indices.push_back(baseIndex + (i + 1)*ringVertexCount + j + 1);
			data.Indices.push_back(baseIndex + i*ringVertexCount + j + 1);

		}
	}
	int southPoleIndex = data.Vertices.size() - 1;
	baseIndex = southPoleIndex - ringVertexCount;
	for (int i = 0; i < sliceCount; i++) {
		data.Indices.push_back(southPoleIndex);
		data.Indices.push_back(baseIndex + i + 1);
		data.Indices.push_back(baseIndex + i);
	}
	return data;
}

Sphere::Sphere() {

}


Sphere::~Sphere() {
}
