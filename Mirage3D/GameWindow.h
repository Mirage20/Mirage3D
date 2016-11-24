#pragma once
#include <string>
#include <Windows.h>
#include <sstream>
#include "Engine.h"
#include "GameTimer.h"

using namespace std;

class GameWindow {
private:
	HINSTANCE mhInstance;
	HWND mhMainWindow;
	int mClientWidth = 800;
	int mClientHeight = 600;
	LPCSTR mMainWindowCaption = "Direct3D11Engine";
	const LPCSTR cWinClassName = "WindowClassD3D11";
	Engine *pGraphicsEngine;
	GameTimer mGametimer;

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK mWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void CalculateFrameStats();
public:
	GameWindow(HINSTANCE hInstance);
	~GameWindow();
	int Run();
};

