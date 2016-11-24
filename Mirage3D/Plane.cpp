#include "Plane.h"





Plane::Plane() {
}


Plane::~Plane() {
}

void Plane::Setup() {
	MeshData m_meshData;

	Vertex vertices[] = {
		{ XMFLOAT3(-1.5f, -1.0f, -1.5f),XMFLOAT3( 0.0f, 1.0f, 0.0f), *(XMFLOAT4*)&Colors::White , XMFLOAT2(1.0f,1.0f) },
		{ XMFLOAT3(+1.5f, -1.0f, -1.5f),XMFLOAT3(0.0f, 1.0f, 0.0f),  *(XMFLOAT4*)&Colors::Black, XMFLOAT2(1.0f,0.0f) },
		{ XMFLOAT3(+1.5f, -1.0f, +1.5f),XMFLOAT3(0.0f, 1.0f, 0.0f),  *(XMFLOAT4*)&Colors::Red , XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(-1.5f, -1.0f, +1.5f),XMFLOAT3(0.0f, 1.0f, 0.0f),  *(XMFLOAT4*)&Colors::Green ,XMFLOAT2(0.0f,1.0f) },
	};

	// Init index
	UINT indices[] = {
		0, 1, 3,
		3, 1, 2,
	};

	int vertexCount = sizeof(vertices) / sizeof(Vertex);
	m_meshData.Vertices.insert(m_meshData.Vertices.begin(), vertices, vertices + vertexCount);

	int indexCount = sizeof(indices) / sizeof(UINT);
	m_meshData.Indices.insert(m_meshData.Indices.begin(), indices, indices + indexCount);

	SetMesh(m_meshData);

	Material mat;
	mat.Name = L"basic";
	mat.Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mat.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mat.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 16.0f);
	mat.TextureName = L"tile";
	SetMaterial(mat);
}

void Plane::Update(float delta, float gameTime) {
	
}