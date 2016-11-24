#pragma once
#include <d3d11.h>
#include <DirectXColors.h>
#include "DataStructures.h"
#include "InputEvent.h"
class Object : public InputEvent {
	friend class Scene;
private:
	MeshData mMeshData;
	Material mMaterial;
	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer* pIndexBuffer;
	ID3D11VertexShader *pVertexShader;
	ID3D11PixelShader *pPixelShader;
	ID3D11ShaderResourceView *pShaderResourceView;
	XMFLOAT4X4 scalingMatrix;
	XMFLOAT4X4 rotationMatrix;
	XMFLOAT4X4 translationMatrix;
	XMFLOAT4X4 m_worldMatrix;

	void BaseSetup();
	void SetDefaultMesh();
	void SetDefaultMaterial();

	void BaseUpdate(float delta, float gameTime);
protected:
	virtual void Setup();
	virtual void Update(float delta, float gameTime);
	void SetMesh(MeshData mesh);
	void SetMaterial(Material material);

public:
	Object();
	void SetPosition(float x, float y, float z);
	void Move(float x, float y, float z);
	void RotateY(float value);
	~Object();
};

