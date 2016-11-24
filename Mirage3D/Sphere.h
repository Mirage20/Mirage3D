#pragma once
#include <d3d11.h>
#include <vector>
#include "DataStructures.h"
#include "Object.h"

class Sphere : public Object {

private:
	void Setup();
	void Update(float delta, float gameTime);
	MeshData CreateSphere(float radius, int sliceCount, int stackCount);
public:
	Sphere();
	~Sphere();
};

