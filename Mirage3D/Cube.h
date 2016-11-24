#pragma once
#include <d3d11.h>
#include <vector>
#include "DataStructures.h"
#include "Object.h"
class Cube : public Object
{


private:
	void Setup();
	void Update(float delta, float gameTime);

protected:
	void OnKeyDown(KeyBoard key);
public:
	Cube();
	~Cube();
};

