#include "GameWindow.h"



GameWindow::GameWindow(HINSTANCE hInstance) : mhInstance(hInstance) {
	
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = cWinClassName;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);
	
	RECT wr = { 0, 0, mClientWidth, mClientHeight };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	mhMainWindow = CreateWindowEx(
		NULL,           // extended window styles
		cWinClassName,    // name of the window class
		mMainWindowCaption,   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		300,    // x-position of the window
		300,    // y-position of the window
		wr.right - wr.left,    // width of the window
		wr.bottom - wr.top,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

	pGraphicsEngine = new Engine(mhMainWindow);
	SetWindowLongPtrW(mhMainWindow, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	
}


GameWindow::~GameWindow() {
	delete pGraphicsEngine;
}

int GameWindow::Run() {

	ShowWindow(mhMainWindow, SW_SHOW);
	mGametimer.Reset();
	MSG msg = {};
	pGraphicsEngine->Initialize();
	while (msg.message != WM_QUIT) {
		// If there are Window messages then process them.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//MessageBox(hWnd, "wew", "wfewf", MB_ABORTRETRYIGNORE);
			mGametimer.Tick();
			CalculateFrameStats();
			pGraphicsEngine->Update(mGametimer.DeltaTime(),mGametimer.GameTime());
			pGraphicsEngine->Render();
		}
	}

	return static_cast<int>(msg.wParam);
}


void GameWindow::CalculateFrameStats() {
		// Code computes the average frames per second, and also the
		// average time it takes to render one frame. These stats
		// are appeneded to the window caption bar.
		static int frameCnt = 0;
		static float timeElapsed = 0.0f;
		frameCnt++;
		// Compute averages over one second period.
		if ((mGametimer.GameTime() - timeElapsed) >= 1.0f) {
			float fps = (float)frameCnt; // fps = frameCnt / 1
			float mspf = 1000.0f / fps;
			std::ostringstream outs;
			outs.precision(6);
			outs << mMainWindowCaption << " "
				<< "FPS: " << fps << " "
				<< "Frame Time: " << mspf << " (ms)";
			SetWindowText(mhMainWindow, outs.str().c_str());
			// Reset for next average.
			frameCnt = 0;
			timeElapsed += 1.0f;
		}
}

LRESULT GameWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	GameWindow* gameWindow = (GameWindow*)(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (gameWindow) return gameWindow->mWindowProc(hwnd, uMsg, wParam, lParam);
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT GameWindow::mWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		//case WM_PAINT:
		////{
		////	PAINTSTRUCT ps;
		////	HDC hdc = BeginPaint(hwnd, &ps);

		////	FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		////	EndPaint(hwnd, &ps);
		////}
		//return 0;
	case WM_KEYDOWN:
		pGraphicsEngine->GetInputManager()->SetKeyDown(wParam);
		break;
	case WM_KEYUP:
		pGraphicsEngine->GetInputManager()->SetKeyUp(wParam);
		break;
	case WM_MOUSEMOVE:
		int xPos = LOWORD(lParam);
		int yPos = HIWORD(lParam);
		if (xPos > 0 && xPos < mClientWidth && yPos > 0 && yPos < mClientHeight) {
			pGraphicsEngine->GetInputManager()->SetMouseMove(xPos, yPos);
			if (xPos != mClientWidth / 2 || yPos != mClientHeight / 2) {
				POINT point;
				point.x = mClientWidth / 2;
				point.y = mClientHeight / 2;
				ClientToScreen(mhMainWindow, &point);
				SetCursorPos(point.x, point.y);
			}
		}
		break;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
