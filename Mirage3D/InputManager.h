#pragma once
#include <vector>
#include "InputEvent.h"
class InputManager {
	friend class GameWindow;
private:
	std::vector<InputEvent*> inputEvents;
	void SetKeyDown(unsigned int key);
	void SetKeyUp(unsigned int key);
	void SetMouseMove(int xPos, int yPos);
public:
	InputManager();
	~InputManager();
	void Register(InputEvent * inputEvent);

};

