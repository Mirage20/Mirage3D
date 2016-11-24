#include "Object.h"
#include "Engine.h"




void Object::BaseSetup() {

	SetDefaultMesh();
	SetDefaultMaterial();

	XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&scalingMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&rotationMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&translationMatrix, XMMatrixIdentity());
	Setup();
	Engine::GetEngine()->GetGraphics()->CreateShaders(mMaterial.Name, &pVertexShader, &pPixelShader);
	Engine::GetEngine()->GetGraphics()->CreateVertexIndexBuffer(&pVertexBuffer, &pIndexBuffer, mMeshData);
	Engine::GetEngine()->GetGraphics()->CreateTexture(mMaterial.TextureName, &pShaderResourceView);
	Engine::GetEngine()->GetInputManager()->Register(this);
}

void Object::SetDefaultMesh() {

	mMeshData.Vertices.clear();
	mMeshData.Indices.clear();

	Vertex vertices[] = {
		{ XMFLOAT3(-0.2f, -0.1f, 0.0f),XMFLOAT3(-0.577f, -0.577f, -0.577f), *(XMFLOAT4*)&Colors::White , XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3( 0.0f, 0.2f, 0.0f),XMFLOAT3(-0.577f, +0.577f, -0.577f),  *(XMFLOAT4*)&Colors::White, XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(0.2f, -0.1f, 0.0f),XMFLOAT3(+0.577f, +0.577f, -0.577f),  *(XMFLOAT4*)&Colors::White , XMFLOAT2(0.0f,0.0f) }
	};

	UINT indices[] = {
		0, 1, 2
	};

	int vertexCount = sizeof(vertices) / sizeof(Vertex);
	mMeshData.Vertices.insert(mMeshData.Vertices.begin(), vertices, vertices + vertexCount);

	int indexCount = sizeof(indices) / sizeof(UINT);
	mMeshData.Indices.insert(mMeshData.Indices.begin(), indices, indices + indexCount);

}

void Object::SetDefaultMaterial() {
	mMaterial.Name = L"default";
	mMaterial.Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mMaterial.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mMaterial.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
}

void Object::Setup() {
}

void Object::BaseUpdate(float delta, float gameTime) {
	
	Engine::GetEngine()->GetGraphics()->SetShader(pVertexShader, pPixelShader);
	Engine::GetEngine()->GetGraphics()->SetVertexIndexBuffer(pVertexBuffer, pIndexBuffer);
	Engine::GetEngine()->GetGraphics()->SetShaderResourceView(pShaderResourceView);
	Update(delta, gameTime);
	XMMATRIX scale = XMLoadFloat4x4(&scalingMatrix);
	XMMATRIX rotation = XMLoadFloat4x4(&rotationMatrix);
	XMMATRIX translation = XMLoadFloat4x4(&translationMatrix);
	XMStoreFloat4x4(&m_worldMatrix, XMMatrixMultiply(translation, XMMatrixMultiply(rotation, scale)));
	Engine::GetEngine()->GetGraphics()->UpdateObject(m_worldMatrix, mMaterial);
	Engine::GetEngine()->GetGraphics()->Draw(mMeshData.Indices.size());
}

void Object::Update(float delta, float gameTime) {

}

void Object::SetMesh(MeshData mesh) {
	if (mesh.Vertices.size() > 0 && mesh.Indices.size() > 0) {
		mMeshData = mesh;
	}
}

void Object::SetMaterial(Material material) {
	mMaterial = material;
}


Object::Object() {

}

void Object::SetPosition(float x, float y, float z) {
	XMStoreFloat4x4(&translationMatrix,  XMMatrixTranspose(XMMatrixTranslation(x, y, z)));
}

void Object::Move(float x, float y, float z) {
	XMStoreFloat4x4(&translationMatrix, XMMatrixMultiply(XMLoadFloat4x4(&translationMatrix), XMMatrixTranspose(XMMatrixTranslation(x, y, z))));
}

void Object::RotateY(float value) {

	XMStoreFloat4x4(&rotationMatrix, XMMatrixMultiply(XMLoadFloat4x4(&rotationMatrix), DirectX::XMMatrixTranspose(
		DirectX::XMMatrixRotationY(
			DirectX::XMConvertToRadians(
				value
			)
		)
	)));
}


Object::~Object() {
	//delete mpMeshData;
	pVertexBuffer->Release();
	pIndexBuffer->Release();
	pVertexShader->Release();
	pPixelShader->Release();
	if (pShaderResourceView != nullptr) {
		pShaderResourceView->Release();
	}
	OutputDebugString("Game Object Desroyed\n");
}
