#include "Texture.h"
#include <D3DX11.h>

Texture::Texture(ID3D11Device* device, LPCSTR path) :
	m_Image(nullptr)
{
	HRESULT hr;

	hr = D3DX11CreateShaderResourceViewFromFileA(device, path, nullptr, nullptr, &m_Image, nullptr);
	if (FAILED(hr))
	{
		throw "Read Image and Create Shader ResourceView Failed";
	}
}

Texture::~Texture()
{
	if (m_Image)
	{
		m_Image->Release();
		m_Image = nullptr;
	}
}

void Texture::bind(ID3D11DeviceContext* deviceContext)
{
	deviceContext->PSSetShaderResources(0, 1, &m_Image);
}