#include "Scene.h"
#include "Sphere.h"


Scene::Scene() {
	camera = new Camera();
	objects.push_back(new Cube());
	objects.push_back(new Plane());
	objects.push_back(new Sphere());
	lights.push_back(new DirectionalLight());
}

Scene::~Scene() {
	delete camera;
	for (size_t i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
	for (size_t i = 0; i < lights.size(); i++) {
		delete lights[i];
	}
}

void Scene::Setup() {
	SetupLights();
	SetupCamera();
	SetupObjects();
}

void Scene::Update(float delta, float gameTime) {
	UpdateLights(delta, gameTime);
	UpdateCamera(delta, gameTime);
	UpdateObjects(delta, gameTime);
}

void Scene::SetupLights() {
	for (size_t i = 0; i < lights.size(); i++) {
		lights[i]->BaseSetup();
	}
}

void Scene::SetupCamera() {
	camera->BaseSetup();
}

void Scene::SetupObjects() {
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->BaseSetup();
	}
}

void Scene::UpdateLights(float delta, float gameTime) {
	for (size_t i = 0; i < lights.size(); i++) {
		lights[i]->BaseUpdate(delta, gameTime);
	}
}

void Scene::UpdateCamera(float delta, float gameTime) {
	camera->BaseUpdate(delta, gameTime);
}

void Scene::UpdateObjects(float delta, float gameTime) {
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->BaseUpdate(delta, gameTime);
	}
}
