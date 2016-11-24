#include "Cube.h"
#include <DirectXColors.h>





Cube::Cube() {

}


Cube::~Cube() {
}


void Cube::Setup() {

	MeshData m_meshData;

	Vertex vertices[] = {
		//front
		{ XMFLOAT3(-0.5f, -0.5f, +0.5f),XMFLOAT3(0.0f,0.0f, 1.0f), *(XMFLOAT4*)&Colors::Red , XMFLOAT2(1.0f,1.0f) },
		{ XMFLOAT3(-0.5f, +0.5f, +0.5f),XMFLOAT3(0.0f,0.0f, 1.0f),  *(XMFLOAT4*)&Colors::Green, XMFLOAT2(1.0f,0.0f) },
		{ XMFLOAT3(+0.5f, +0.5f, +0.5f),XMFLOAT3(0.0f,0.0f, 1.0f),  *(XMFLOAT4*)&Colors::Blue , XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(+0.5f, -0.5f, +0.5f),XMFLOAT3(0.0f,0.0f, 1.0f),  *(XMFLOAT4*)&Colors::Yellow ,XMFLOAT2(0.0f,1.0f) },
		//back
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f),XMFLOAT3(0.0f,0.0f, -1.0f), *(XMFLOAT4*)&Colors::Red , XMFLOAT2(1.0f,1.0f) },
		{ XMFLOAT3(-0.5f, +0.5f, -0.5f),XMFLOAT3(0.0f,0.0f, -1.0f),  *(XMFLOAT4*)&Colors::Green, XMFLOAT2(1.0f,0.0f) },
		{ XMFLOAT3(+0.5f, +0.5f, -0.5f),XMFLOAT3(0.0f,0.0f, -1.0f),  *(XMFLOAT4*)&Colors::Blue , XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(+0.5f, -0.5f, -0.5f),XMFLOAT3(0.0f,0.0f, -1.0f),  *(XMFLOAT4*)&Colors::Yellow ,XMFLOAT2(0.0f,1.0f) },
		//left
		{ XMFLOAT3(-0.5f, -0.5f, +0.5f),XMFLOAT3(-1.0f,0.0f, 0.0f), *(XMFLOAT4*)&Colors::Red , XMFLOAT2(1.0f,1.0f) },
		{ XMFLOAT3(-0.5f, +0.5f, +0.5f),XMFLOAT3(-1.0f,0.0f, 0.0f),  *(XMFLOAT4*)&Colors::Green, XMFLOAT2(1.0f,0.0f) },
		{ XMFLOAT3(-0.5f, +0.5f, -0.5f),XMFLOAT3(-1.0f,0.0f, 0.0f),  *(XMFLOAT4*)&Colors::Blue , XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f),XMFLOAT3(-1.0f,0.0f, 0.0f),  *(XMFLOAT4*)&Colors::Yellow ,XMFLOAT2(0.0f,1.0f) },
		//right
		{ XMFLOAT3(+0.5f, -0.5f, +0.5f),XMFLOAT3(1.0f,0.0f, 0.0f), *(XMFLOAT4*)&Colors::Red , XMFLOAT2(1.0f,1.0f) },
		{ XMFLOAT3(+0.5f, +0.5f, +0.5f),XMFLOAT3(1.0f,0.0f, 0.0f),  *(XMFLOAT4*)&Colors::Green, XMFLOAT2(1.0f,0.0f) },
		{ XMFLOAT3(+0.5f, +0.5f, -0.5f),XMFLOAT3(1.0f,0.0f, 0.0f),  *(XMFLOAT4*)&Colors::Blue , XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(+0.5f, -0.5f, -0.5f),XMFLOAT3(1.0f,0.0f, 0.0f),  *(XMFLOAT4*)&Colors::Yellow ,XMFLOAT2(0.0f,1.0f) },
		//top
		{ XMFLOAT3(-0.5f, +0.5f, +0.5f),XMFLOAT3(0.0f,1.0f, 0.0f), *(XMFLOAT4*)&Colors::Red , XMFLOAT2(1.0f,1.0f) },
		{ XMFLOAT3(-0.5f, +0.5f, -0.5f),XMFLOAT3(0.0f,1.0f, 0.0f),  *(XMFLOAT4*)&Colors::Green, XMFLOAT2(1.0f,0.0f) },
		{ XMFLOAT3(+0.5f, +0.5f, -0.5f),XMFLOAT3(0.0f,1.0f, 0.0f),  *(XMFLOAT4*)&Colors::Blue , XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(+0.5f, +0.5f, +0.5f),XMFLOAT3(0.0f,1.0f, 0.0f),  *(XMFLOAT4*)&Colors::Yellow ,XMFLOAT2(0.0f,1.0f) },
		//bottom
		{ XMFLOAT3(-0.5f, -0.5f, +0.5f),XMFLOAT3(0.0f,-1.0f, 0.0f), *(XMFLOAT4*)&Colors::Red , XMFLOAT2(1.0f,1.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f),XMFLOAT3(0.0f,-1.0f, 0.0f),  *(XMFLOAT4*)&Colors::Green, XMFLOAT2(1.0f,0.0f) },
		{ XMFLOAT3(+0.5f, -0.5f, -0.5f),XMFLOAT3(0.0f,-1.0f, 0.0f),  *(XMFLOAT4*)&Colors::Blue , XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(+0.5f, -0.5f, +0.5f),XMFLOAT3(0.0f,-1.0f, 0.0f),  *(XMFLOAT4*)&Colors::Yellow ,XMFLOAT2(0.0f,1.0f) },
	};

	// Init index
	UINT indices[] = {
		// front face
		0, 1, 2,
		0, 2, 3,
		// back face
		4, 7, 6,
		4, 6, 5,
		// left face
		11, 10, 9,
		11, 9, 8,
		// right face
		12, 13, 14,
		12, 14, 15,
		// top face
		16, 17, 18,
		16, 18, 19,
		// bottom face
		20, 22, 21,
		20, 23, 22
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
	mat.TextureName = L"sample";
	SetMaterial(mat);
}

void Cube::Update(float delta, float gameTime) {
	RotateY(-delta * 20);
}

void Cube::OnKeyDown(KeyBoard key) {
	if (key == KeyBoard::LEFT_ARROW) {
		Move(1.0f, 0.0f, 0.0f);
	}
	else if(key == KeyBoard::RIGHT_ARROW) {
		Move(-1.0f, 0.0f, 0.0f);
	}
}
