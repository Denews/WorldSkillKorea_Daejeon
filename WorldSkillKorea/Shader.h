#pragma once
#include <D3D11.h>

const class Shader
{
public:
	Shader() = delete;
	Shader(Shader&) = delete;
	Shader(ID3D11Device* device);
	~Shader();

	void bind(ID3D11DeviceContext* deviceContext);
private:
	ID3D11InputLayout* m_InputLayout;
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
};