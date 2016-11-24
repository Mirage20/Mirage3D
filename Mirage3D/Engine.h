#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <DirectXColors.h>
#include <vector>
#include <D3Dcompiler.h>
#include "ShaderManager.h"
#include "DataStructures.h"
#include "Graphics.h"
#include "InputManager.h"
#include "Scene.h"

using namespace DirectX;

class Engine {
private:

	HWND hWnd;	
	Graphics m_graphics;
	InputManager mInputManager;
	Scene scene;

	static Engine* ps_engine;

	void SetupObjects();

public:
	Engine(HWND hWnd);
	~Engine();

	bool Initialize();
	
	void Update(float delta, float gameTime);
	void Render();
	void SendKey(unsigned int key);
	Graphics* GetGraphics();
	InputManager* GetInputManager();
	static Engine* GetEngine();

};

