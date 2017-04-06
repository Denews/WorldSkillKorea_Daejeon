#pragma once
#include <D3D11.h>

const class Texture
{
public:
	Texture() = delete;
	Texture(Texture&) = delete;
	Texture(ID3D11Device* device, LPCSTR path);
	~Texture();

	void bind(ID3D11DeviceContext* deviceContext);
private:
	ID3D11ShaderResourceView* m_Image;
};