#pragma once
#include<DirectXMath.h>
#include "InputEvent.h"

using namespace DirectX;

class Camera : public InputEvent {
	friend class Scene;

private:

	XMFLOAT4 position;
	XMFLOAT4 target;
	XMFLOAT4 up;
	XMFLOAT3 direction;
	float fov;
	float nearZ;
	float farZ;
	float moveSpeed;
	int yaw;
	int pitch;
	int forward;
	int side;
	int raise;
	void BaseSetup();
	void BaseUpdate(float delta, float gameTime);
protected:
	void OnKeyDown(KeyBoard key);
	void OnKeyUp(KeyBoard key);
	void OnMouseMove(int xPos, int yPos);
public:
	Camera();
	~Camera();
	void Setup();
	void Update(float delta, float gameTime);
	
};

