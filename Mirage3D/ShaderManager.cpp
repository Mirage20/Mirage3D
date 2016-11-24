#include "ShaderManager.h"
#include <string>


int Shaders::FindShader(std::wstring shaderName) {
	
	for (size_t i = 0; i < shaders.size(); i++) {
		if (shaders[i].shaderName.compare(shaderName) == 0) {
			return i;
		}
	}
	return -1;
}

Shaders::Shaders() {
}

bool Shaders::Initialize() {
	return false;
}

Shader Shaders::GetShader(std::wstring shaderName) {

	int shaderIndex = FindShader(shaderName);
	if (shaderIndex >= 0) {
		return shaders[shaderIndex];
	}

	Shader shader;
	HRESULT hr;
	ID3DBlob *bError;

	shader.shaderName = shaderName;

	std::wstring shaderPath = L"Shaders\\" + shaderName + L".hlsl";
	hr = D3DCompileFromFile(shaderPath.c_str(), NULL, NULL, "vMain", "vs_5_0", D3DCOMPILE_DEBUG, NULL, &shader.bVertexShader, &bError);

	if (bError != NULL) {
		LPSTR errorMsg = (LPSTR)bError->GetBufferPointer();
		MessageBox(NULL, errorMsg, "Error Vertex Shader", MB_OK);
	}

	hr = D3DCompileFromFile(shaderPath.c_str(), NULL, NULL, "pMain", "ps_5_0", D3DCOMPILE_DEBUG , NULL, &shader.bPixelShader, &bError);

	if (bError != NULL) {
		LPSTR errorMsg = (LPSTR)bError->GetBufferPointer();
		MessageBox(NULL, errorMsg, "Error Pixel Shader", MB_OK);
	}

	shaders.push_back(shader);
	return shader;
}


Shaders::~Shaders() {
}
