#pragma once
#include<DirectXMath.h>

using namespace DirectX;

class DirectionalLight {
	friend class Scene;
public:

	struct Data {
		XMFLOAT4 Ambient;
		XMFLOAT4 Diffuse;
		XMFLOAT4 Specular;
		XMFLOAT3 Direction;
		float Pad; // Pad the last float so we can
				   // array of lights if we wanted.
	};
private:

	Data lightData;
	void BaseSetup();
	void BaseUpdate(float delta, float gameTime);

public:

	DirectionalLight();
	~DirectionalLight();
	void Setup();
	int GetID();
	Data GetData();
	void Update(float delta, float gameTime);
};

