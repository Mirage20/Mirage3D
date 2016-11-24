#pragma once

enum class KeyBoard : unsigned int{
	A = 0x41,
	D = 0x44,
	E = 0x45,
	Q = 0x51,
	S = 0x53,
	W = 0x57,
	LEFT_ARROW = 0x25,
	UP_ARROW = 0x26,
	RIGHT_ARROW = 0x27,
	DOWN_ARROW = 0x28
};

class InputEvent {
	friend class InputManager;
protected:
	virtual void OnKeyDown(KeyBoard keyboard);
	virtual void OnKeyUp(KeyBoard keyboard);
	virtual void OnMouseMove(int xPos, int yPos);
public:
	InputEvent();
	~InputEvent();
	

};

