#include "DirectionalLight.h"
#include "Engine.h"


void DirectionalLight::BaseSetup() {
	lightData.Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	lightData.Diffuse = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	lightData.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	lightData.Direction = XMFLOAT3(0.0f, -0.49f, -0.86f);
	Setup();
	Engine::GetEngine()->GetGraphics()->UpdateDirectionalLight(this);
}

void DirectionalLight::BaseUpdate(float delta, float gameTime) {
	Update(delta, gameTime);
	Engine::GetEngine()->GetGraphics()->UpdateDirectionalLight(this);
}

DirectionalLight::DirectionalLight() {
}


DirectionalLight::~DirectionalLight() {
}

void DirectionalLight::Setup() {
}

int DirectionalLight::GetID() {
	return 0;
	
}

DirectionalLight::Data DirectionalLight::GetData() {
	return lightData;
}

void DirectionalLight::Update(float delta, float gameTime) {
}
