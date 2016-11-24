#pragma once
#include <DirectXMath.h>
#include <vector>
using namespace DirectX;

struct Vertex {
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
	XMFLOAT4 Color;
	XMFLOAT2 Texture;
};

struct MeshData {
	std::vector<Vertex> Vertices;
	std::vector<UINT> Indices;
};

struct Material {
	std::wstring Name;
	std::wstring TextureName;
	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Specular;
};

struct ConstantBufferObject {
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
	XMFLOAT4X4 worldInvTrans;
	XMFLOAT4X4 textureTransform;
	
	XMFLOAT4 MAmbient;
	XMFLOAT4 MDiffuse;
	XMFLOAT4 MSpecular;

};
