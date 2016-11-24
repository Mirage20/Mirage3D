#include "Engine.h"
#include <DirectXTex.h>

Engine* Engine::ps_engine = nullptr;

Engine::Engine(HWND hWnd) : hWnd(hWnd) , m_graphics(hWnd){
	ps_engine = this;
}


Engine::~Engine() {

}

bool Engine::Initialize() {


	m_graphics.Initialize();

	
	SetupObjects();

	//InitializePipeline();

	//SetupTexture();
	//SetupWorld();
	//SetupGeometry();



	return true;
}



void Engine::SetupObjects() {
	scene.Setup();
}


void Engine::Update(float delta, float gameTime) {

	m_graphics.Clear();

	scene.Update(delta, gameTime);

	// gggg
	//a = 30 * delta;
	//DirectX::XMStoreFloat4x4(
	//	&m_constantBuffeObject.world,
	//	DirectX::XMMatrixTranspose(
	//		DirectX::XMMatrixRotationY(
	//			DirectX::XMConvertToRadians(
	//				a
	//			)
	//		)
	//	)
	//);
	m_graphics.Present();
	/*DirectX::XMStoreFloat4x4(&m_constantBuffeObject.worldInvTrans,
		XMMatrixTranspose(XMMatrixInverse(nullptr, (XMLoadFloat4x4(&m_constantBuffeObject.world)))));*/

	//DirectX::XMStoreFloat4x4(&m_constantBufferData.worldInvTrans, XMMatrixInverse(nullptr,XMMatrixTranspose(XMLoadFloat4x4(&m_constantBufferData.world))));
	
	//c1.Move(delta/2, 0.0f, 0.0f);
	//c2.SetPosition(-1.0f, 0.0f, 0.0f);
	//c2.RotateY(a);
	//c1.RotateY(-a);
	//m_constantBuffeFrame.gTime = gameTime;
}

void Engine::Render() {
	//pDeviceContext->ClearRenderTargetView(pRenderTargetView, Colors::Black);
	//pDeviceContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//pDeviceContext->UpdateSubresource(
	//	mConstantBufferFrame,
	//	0,
	//	nullptr,
	//	&m_constantBuffeFrame,
	//	0,
	//	0
	//);

	//
	//DrawObject(c1);
	//DrawObject(c2);

	//UINT stride = sizeof(Vertex);
	//UINT offset = 0;
	//pDeviceContext->IASetVertexBuffers(0, 1, &pVB, &stride, &offset);

	//// select which primtive type we are using
	////pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//pDeviceContext->Draw(8, 0);

	//pSwapChain->Present(0, 0);

	//DirectX::XMStoreFloat4x4(
	//	&m_constantBufferData.world,
	//	DirectX::XMMatrixTranspose(
	//		DirectX::XMMatrixRotationY(
	//			DirectX::XMConvertToRadians(
	//			(float)m_frameCount++
	//			)
	//		)
	//	)
	//);

	
	/*pSwapChain->Present(0, 0);*/

}

void Engine::SendKey(unsigned int key)
{
	switch (key)
	{
	case VK_LEFT:

		// Process the LEFT ARROW key. 
		//XMVECTOR b = XMQuaternionRotationAxis(XMLoadFloat3(&XMFLOAT3(0.0f, 1.0f, 0.0f)), 0.1f);
		//XMVECTOR a = XMVector3Rotate(XMLoadFloat3(&m_constantBufferData.Direction), b);
		//XMStoreFloat3(&m_constantBufferData.Direction,a);
		//m_constantBufferData.Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
		//m_constantBuffeFrame.eyePos.z += 1;
		break;

	case VK_RIGHT:

		// Process the RIGHT ARROW key. 

		break;

	case VK_UP:

		// Process the UP ARROW key. 

		break;

	case VK_DOWN:

		// Process the DOWN ARROW key. 

		break;

	case VK_HOME:

		// Process the HOME key. 

		break;

	case VK_END:

		// Process the END key. 

		break;

	case VK_INSERT:

		// Process the INS key. 

		break;

	case VK_DELETE:

		// Process the DEL key. 

		break;

	case VK_F2:

		// Process the F2 key. 

		break;


		// Process other non-character keystrokes. 

	default:
		break;
	}
}

Graphics* Engine::GetGraphics() {
	return &ps_engine->m_graphics;
}

InputManager * Engine::GetInputManager() {
	return &ps_engine->mInputManager;
}



Engine * Engine::GetEngine() {
	return ps_engine;
}
