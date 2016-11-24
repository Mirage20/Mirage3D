#pragma once
#include <Windows.h>
#include <D3Dcompiler.h>
#include <vector>

struct Shader {
	std::wstring shaderName;
	ID3DBlob *bVertexShader;
	ID3DBlob *bPixelShader;
};


class Shaders {

private:
	std::vector<Shader> shaders;

	int FindShader(std::wstring shaderName);

public:
	Shaders();
	bool Initialize();
	Shader GetShader(std::wstring shaderName);
	~Shaders();
};

