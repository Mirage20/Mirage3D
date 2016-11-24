#include "InputManager.h"
#include <Windows.h>
#include <string>

InputManager::InputManager() {
}


InputManager::~InputManager() {
}

void InputManager::Register(InputEvent * inputEvent) {
	inputEvents.push_back(inputEvent);
}

void InputManager::SetKeyDown(unsigned int key) {
	for (size_t i = 0; i < inputEvents.size(); i++) {
		inputEvents[i]->OnKeyDown(static_cast<KeyBoard>(key));
	}
}

void InputManager::SetKeyUp(unsigned int key) {
	for (size_t i = 0; i < inputEvents.size(); i++) {
		inputEvents[i]->OnKeyUp(static_cast<KeyBoard>(key));
	}
}

void InputManager::SetMouseMove(int x, int y) {
	for (size_t i = 0; i < inputEvents.size(); i++) {
		inputEvents[i]->OnMouseMove(x, y);
	}
}
