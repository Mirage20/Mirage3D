#pragma once
#include <Windows.h>
#include <d3d11.h>
#include "ShaderManager.h"
#include "DataStructures.h"
#include "DirectionalLight.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib") 
#pragma comment (lib, "D3DCompiler.lib")

class Graphics {

private:

	struct ConstantBufferFrame {
		DirectionalLight::Data light[2];
		XMFLOAT3 eyePos;
		float gTime = 0;
	};

	HWND hWnd;
	Shaders shaders;

	ID3D11Device *pDevice;
	ID3D11DeviceContext *pDeviceContext;
	IDXGISwapChain *pSwapChain;
	ID3D11RenderTargetView* pRenderTargetView;
	ID3D11Texture2D* pDepthStencilBuffer;
	ID3D11DepthStencilView* pDepthStencilView;
	ID3D11InputLayout *pInputLayout;

	ID3D11Buffer *mConstantBufferObject;
	ID3D11Buffer *mConstantBufferFrame;
	ConstantBufferObject m_constantBuffeObject;
	ConstantBufferFrame m_constantBuffeFrame;

	int mClientWidth = 800;
	int mClientHeight = 600;

	bool InitializeShaders();
	bool InitializeConstantBuffer();
	void SetupSampler();
	void SetupWorld();

public:
	Graphics(HWND hWnd);
	~Graphics();
	bool Initialize();
	bool CreateShaders(std::wstring shaderName, ID3D11VertexShader **vs, ID3D11PixelShader **ps) ;
	void SetShader(ID3D11VertexShader *vs, ID3D11PixelShader *ps) ;
	bool CreateTexture(std::wstring textureName, ID3D11ShaderResourceView **srv);
	void SetShaderResourceView(ID3D11ShaderResourceView *srv);
	bool CreateVertexIndexBuffer(ID3D11Buffer **vb, ID3D11Buffer **ib, MeshData meshData) ;
	void SetVertexIndexBuffer(ID3D11Buffer *vb, ID3D11Buffer *ib) ;
	void Draw(int veterxcount);
	void UpdateObject(XMFLOAT4X4 world, Material material);
	void UpdateDirectionalLight(DirectionalLight *light);
	void Clear();
	void SetView(XMFLOAT4 eye, XMFLOAT4 target, XMFLOAT4 up);
	void SetProjection(float fov, float nearZ, float farZ);
	void Present();
};

