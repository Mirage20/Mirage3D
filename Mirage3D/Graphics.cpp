#include "Graphics.h"
#include <DirectXColors.h>
#include <DirectXTex.h>



Graphics::Graphics(HWND hWnd) : hWnd(hWnd) {

}


Graphics::~Graphics() {
	
	mConstantBufferObject->Release();
	mConstantBufferFrame->Release();
	
	
	pDepthStencilBuffer->Release();
	pDepthStencilView->Release();
	pInputLayout->Release();

	pRenderTargetView->Release();
	pSwapChain->Release();
	pDeviceContext->Release();
	pDevice->Release();
}

bool Graphics::Initialize() {
	D3D_FEATURE_LEVEL featureLevels[4] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3
	};
	D3D_FEATURE_LEVEL featureLevel;

	//IDXGIFactory* pFactory = nullptr;
	//if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory)))) {
	//	MessageBox(0, "CreateDXGIFactory1 FAILED on adapter enumeration.", 0, 0);
	//	return false;
	//}

	//UINT i = 0;
	//IDXGIAdapter * pAdapter;
	//std::vector <IDXGIAdapter*> vAdapters;
	//while (pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND) {
	//	vAdapters.push_back(pAdapter);
	//	++i;
	//}

	HRESULT hr = D3D11CreateDevice(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevels,
		4,
		D3D11_SDK_VERSION,
		&pDevice,
		&featureLevel,
		&pDeviceContext
	);

	if (FAILED(hr)) {
		MessageBox(0, "D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0) {
		MessageBox(0, "Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	//Create swap chain
	DXGI_SWAP_CHAIN_DESC sd;

	sd.BufferDesc.Width = mClientWidth;
	sd.BufferDesc.Height = mClientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = NULL;

	IDXGIDevice * pDXGIDevice = nullptr;
	hr = pDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);

	IDXGIAdapter * pDXGIAdapter = nullptr;
	hr = pDXGIDevice->GetAdapter(&pDXGIAdapter);

	IDXGIFactory * pIDXGIFactory = nullptr;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&pIDXGIFactory);

	hr = pIDXGIFactory->CreateSwapChain(
		pDevice,
		&sd,
		&pSwapChain
	);

	pDXGIDevice->Release();
	pDXGIAdapter->Release();
	pIDXGIFactory->Release();


	// Create render target
	ID3D11Texture2D *backBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	pDevice->CreateRenderTargetView(backBuffer, NULL, &pRenderTargetView);
	backBuffer->Release();


	//Create depth stencill buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = mClientWidth;
	depthStencilDesc.Height = mClientHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = NULL;
	depthStencilDesc.MiscFlags = NULL;

	pDevice->CreateTexture2D(&depthStencilDesc, 0, &pDepthStencilBuffer);
	pDevice->CreateDepthStencilView(pDepthStencilBuffer, NULL, &pDepthStencilView);

	//bind view to output merger state
	pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);

	//Set viewport
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = static_cast<float>(mClientWidth);
	vp.Height = static_cast<float>(mClientHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	pDeviceContext->RSSetViewports(1, &vp);

	InitializeShaders();
	InitializeConstantBuffer();
	SetupSampler();
	SetupWorld();

	return true;
}

bool Graphics::InitializeShaders() {

	Shader shader = shaders.GetShader(L"basic");
	HRESULT hr;

	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXTURE",0,DXGI_FORMAT_R32G32_FLOAT,0,40,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};

	hr = pDevice->CreateInputLayout(desc, 4, shader.bVertexShader->GetBufferPointer(), shader.bVertexShader->GetBufferSize(), &pInputLayout);
	pDeviceContext->IASetInputLayout(pInputLayout);
	return true;
}

bool Graphics::InitializeConstantBuffer() {
	HRESULT hr;

	D3D11_BUFFER_DESC cbDescObject;
	cbDescObject.Usage = D3D11_USAGE_DEFAULT;
	cbDescObject.ByteWidth = sizeof(ConstantBufferObject);
	cbDescObject.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDescObject.CPUAccessFlags = 0;
	cbDescObject.MiscFlags = 0;
	cbDescObject.StructureByteStride = 0;

	hr = pDevice->CreateBuffer(&cbDescObject, nullptr, &mConstantBufferObject);

	D3D11_BUFFER_DESC cbDescFrame;
	cbDescFrame.Usage = D3D11_USAGE_DEFAULT;
	cbDescFrame.ByteWidth = sizeof(ConstantBufferFrame);
	cbDescFrame.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDescFrame.CPUAccessFlags = 0;
	cbDescFrame.MiscFlags = 0;
	cbDescFrame.StructureByteStride = 0;
	hr = pDevice->CreateBuffer(&cbDescFrame, nullptr, &mConstantBufferFrame);

	pDeviceContext->VSSetConstantBuffers(0, 1, &mConstantBufferObject);
	pDeviceContext->VSSetConstantBuffers(1, 1, &mConstantBufferFrame);
	pDeviceContext->PSSetConstantBuffers(0, 1, &mConstantBufferObject);
	pDeviceContext->PSSetConstantBuffers(1, 1, &mConstantBufferFrame);

	return true;

}

void Graphics::SetupSampler() {
	// temp 
	ID3D11SamplerState *samplerSate;
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
	samplerDesc.MaxAnisotropy = 4;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;;
	pDevice->CreateSamplerState(&samplerDesc, &samplerSate);
	pDeviceContext->PSSetSamplers(0, 1, &samplerSate);
	samplerSate->Release();

}

void Graphics::SetupWorld() {


	XMStoreFloat4x4(&m_constantBuffeObject.world, XMMatrixIdentity());
	XMStoreFloat4x4(&m_constantBuffeObject.worldInvTrans, XMMatrixIdentity());
	XMStoreFloat4x4(&m_constantBuffeObject.textureTransform, XMMatrixIdentity());



	DirectX::XMStoreFloat4x4(&m_constantBuffeObject.textureTransform, XMLoadFloat4x4(&m_constantBuffeObject.world));

}

bool Graphics::CreateShaders(std::wstring shaderName, ID3D11VertexShader ** vs, ID3D11PixelShader ** ps) {

	Shader shader = shaders.GetShader(shaderName.c_str());

	HRESULT hr;
	hr = pDevice->CreateVertexShader(shader.bVertexShader->GetBufferPointer(), shader.bVertexShader->GetBufferSize(), NULL, vs);
	hr = pDevice->CreatePixelShader(shader.bPixelShader->GetBufferPointer(), shader.bPixelShader->GetBufferSize(), NULL, ps);

	return true;
}

bool Graphics::CreateVertexIndexBuffer(ID3D11Buffer ** vb, ID3D11Buffer ** ib, MeshData meshData) {


	// Create vertex buffer
	D3D11_BUFFER_DESC vbDesc;
	vbDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vbDesc.ByteWidth = sizeof(Vertex) * meshData.Vertices.size();      //change
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.CPUAccessFlags = 0;
	vbDesc.MiscFlags = 0;
	vbDesc.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vbData;
	vbData.pSysMem = &meshData.Vertices.front();
	vbData.SysMemPitch = 0;
	vbData.SysMemSlicePitch = 0;
	pDevice->CreateBuffer(&vbDesc, &vbData, vb);

	// Create index buffer
	D3D11_BUFFER_DESC ibDesc;
	ibDesc.Usage = D3D11_USAGE_IMMUTABLE;
	ibDesc.ByteWidth = sizeof(UINT) * meshData.Indices.size();;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;
	ibDesc.MiscFlags = 0;
	ibDesc.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA ibData;
	ibData.pSysMem = &meshData.Indices.front();
	ibData.SysMemPitch = 0;
	ibData.SysMemSlicePitch = 0;
	pDevice->CreateBuffer(&ibDesc, &ibData, ib);

	return false;
}

void Graphics::SetShader(ID3D11VertexShader * vs, ID3D11PixelShader * ps) {
	pDeviceContext->VSSetShader(vs, NULL, 0);
	pDeviceContext->PSSetShader(ps, NULL, 0);

}

bool Graphics::CreateTexture(std::wstring textureName, ID3D11ShaderResourceView ** srv) {
	ScratchImage image;

	HRESULT hr = LoadFromWICFile((L"Textures\\" + textureName + L".jpg").c_str(), WIC_FLAGS_NONE, nullptr, image);

	if (SUCCEEDED(hr)) {
		hr = CreateShaderResourceView(pDevice, image.GetImages(), image.GetImageCount(), image.GetMetadata(), srv);
	}
	return false;
}

void Graphics::SetShaderResourceView(ID3D11ShaderResourceView * srv) {
		pDeviceContext->PSSetShaderResources(0, 1, &srv);
}

void Graphics::SetVertexIndexBuffer(ID3D11Buffer * vb, ID3D11Buffer * ib) {
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
	pDeviceContext->IASetIndexBuffer(ib, DXGI_FORMAT_R32_UINT, 0);
}

void Graphics::Draw(int veterxcount) {
	pDeviceContext->DrawIndexed(veterxcount, 0, 0);
}

void Graphics::UpdateObject(XMFLOAT4X4 world, Material material) {



	XMStoreFloat4x4(&m_constantBuffeObject.world, XMLoadFloat4x4(&world));
	DirectX::XMStoreFloat4x4(&m_constantBuffeObject.worldInvTrans, XMMatrixTranspose(XMMatrixInverse(nullptr, (XMLoadFloat4x4(&m_constantBuffeObject.world)))));

	m_constantBuffeObject.MAmbient = material.Ambient;
	m_constantBuffeObject.MDiffuse = material.Diffuse;
	m_constantBuffeObject.MSpecular = material.Specular;

	pDeviceContext->UpdateSubresource(
		mConstantBufferObject,
		0,
		nullptr,
		&m_constantBuffeObject,
		0,
		0
	);
}

void Graphics::UpdateDirectionalLight(DirectionalLight *light) {

	int id = light->GetID();
	m_constantBuffeFrame.light[id] = light->GetData();


	pDeviceContext->UpdateSubresource(
		mConstantBufferFrame,
		0,
		nullptr,
		&m_constantBuffeFrame,
		0,
		0
	);
}

void Graphics::Clear() {
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, Colors::Black);
	pDeviceContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Graphics::SetView(XMFLOAT4 eye, XMFLOAT4 target, XMFLOAT4 up) {

	m_constantBuffeFrame.eyePos.x = eye.x;
	m_constantBuffeFrame.eyePos.y = eye.y;
	m_constantBuffeFrame.eyePos.z = eye.z;

	DirectX::XMStoreFloat4x4(
		&m_constantBuffeObject.view,
		DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtRH(
			XMLoadFloat4(&eye), 
			XMLoadFloat4(&target),
			XMLoadFloat4(&up))
		)
	);
}

void Graphics::SetProjection(float fov, float nearZ, float farZ) {
	
	float aspectRatio = mClientWidth / (float)mClientHeight;

	DirectX::XMStoreFloat4x4(
		&m_constantBuffeObject.projection,
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixPerspectiveFovRH(
				DirectX::XMConvertToRadians(fov),
				aspectRatio,
				nearZ,
				farZ
			)
		)
	);
}

void Graphics::Present() {
	pSwapChain->Present(0, 0);
}



