#include <Windows.h>
#include "GameWindow.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	GameWindow gameWindow(hInstance);
	int result = gameWindow.Run();
	
	return result;
}

