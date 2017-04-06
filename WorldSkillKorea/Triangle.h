#pragma once
#include <D3D11.h>

class Triangle
{
public:
	Triangle(ID3D11Device* device);

	void draw(ID3D11DeviceContext* deviceContext);
private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
};