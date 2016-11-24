#include "Camera.h"
#include "Engine.h"


void Camera::BaseSetup() {
	position = XMFLOAT4(0.0f, 0.7f, 1.5f, 0.f);
	target = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.f);
	up = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.f);
	fov = 70;
	nearZ = 0.01f;
	farZ = 100.0f;
	moveSpeed = 1;
	XMStoreFloat3(&direction, XMVector4Normalize(XMVectorSubtract(XMLoadFloat4(&target), XMLoadFloat4(&position))));
	target.x = position.x + direction.x;
	target.y = position.y + direction.y;
	target.z = position.z + direction.z;
	yaw = 0;
	pitch = 0;
	forward = 0;
	side = 0;
	raise = 0;
	Setup();
	Engine::GetEngine()->GetGraphics()->SetView(position, target, up);
	Engine::GetEngine()->GetGraphics()->SetProjection(fov, nearZ, farZ);
	Engine::GetEngine()->GetInputManager()->Register(this);
}

void Camera::BaseUpdate(float delta, float gameTime) {
	target.x = position.x + direction.x;
	target.y = position.y + direction.y;
	target.z = position.z + direction.z;
	Update(delta, gameTime);
	Engine::GetEngine()->GetGraphics()->SetView(position, target, up);
	Engine::GetEngine()->GetGraphics()->SetProjection(fov, nearZ, farZ);
}

Camera::Camera() {
}

Camera::~Camera() {
}

void Camera::Setup() {
}

void Camera::Update(float delta, float gameTime) {
	position.x += forward * direction.x * moveSpeed * delta;
	position.y += forward * direction.y * moveSpeed * delta;
	position.z += forward * direction.z * moveSpeed * delta;

	XMFLOAT3 deltaPosition;
	XMStoreFloat3(&deltaPosition, XMVector3Cross(XMLoadFloat3(&direction), XMLoadFloat4(&up)));
	position.x += side * deltaPosition.x * moveSpeed * delta;
	position.y += side * deltaPosition.y * moveSpeed * delta;
	position.z += side * deltaPosition.z * moveSpeed * delta;

	position.y += raise * moveSpeed * delta;
	//XMStoreFloat3(&direction, XMVector3Transform(XMLoadFloat3(&direction), XMMatrixRotationAxis(XMLoadFloat4(&up), -0.001f * yaw)));

	//XMStoreFloat3(&direction, XMVector3Transform(XMLoadFloat3(&direction), XMMatrixRotationAxis(XMVector3Cross(XMLoadFloat4(&up), XMLoadFloat3(&direction)), 0.001f * pitch)));

}

void Camera::OnKeyDown(KeyBoard key) {
	if (key == KeyBoard::W) {
		forward = 1;
	}
	else if (key == KeyBoard::S) {
		forward = -1;
	}
	else if (key == KeyBoard::A) {
		side = -1;
	}
	else if (key == KeyBoard::D) {
		side = 1;
	}
	else if (key == KeyBoard::E) {
		raise = -1;
	}
	else if (key == KeyBoard::Q) {
		raise = 1;
	}
}

void Camera::OnKeyUp(KeyBoard key) {
	if (key == KeyBoard::W || key == KeyBoard::S) {
		forward = 0;
	}
	else if(key == KeyBoard::A || key == KeyBoard::D){
		side = 0;
	}
	else if (key == KeyBoard::E || key == KeyBoard::Q) {
		raise = 0;
	}
}

void Camera::OnMouseMove(int xPos, int yPos) {

	XMStoreFloat3(&direction, XMVector3Transform(XMLoadFloat3(&direction), XMMatrixRotationAxis(XMLoadFloat4(&up), -0.001f * (xPos - 400))));

	XMStoreFloat3(&direction, XMVector3Transform(XMLoadFloat3(&direction), XMMatrixRotationAxis(XMVector3Cross(XMLoadFloat4(&up), XMLoadFloat3(&direction)), 0.001f * (yPos - 300))));
	yaw = xPos - 400;
	pitch = yPos - 300;
	//preMouseX = xPos;
	//preMouseY = yPos;
}
