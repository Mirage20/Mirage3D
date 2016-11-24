#pragma once
#include <vector>
#include "Object.h"
#include "Cube.h"
#include "Plane.h"
#include "Camera.h"
#include "DirectionalLight.h"
class Scene {

private:
	std::vector<Object*> objects;
	std::vector<DirectionalLight*> lights;
	Camera * camera;
	void SetupLights();
	void SetupCamera();
	void SetupObjects();
	void UpdateLights(float delta, float gameTime);
	void UpdateCamera(float delta, float gameTime);
	void UpdateObjects(float delta, float gameTime);

public:
	Scene();
	~Scene();
	void Setup();
	void Update(float delta, float gameTime);
};

