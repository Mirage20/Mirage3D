#pragma once
#include "Object.h"

class Plane : public Object{
private:
	void Setup();
	void Update(float delta, float gameTime);
public:
	Plane();
	~Plane();
};

