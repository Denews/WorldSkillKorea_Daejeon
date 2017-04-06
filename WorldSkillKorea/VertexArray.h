#pragma once
#include <D3D11.h>
#include <xnamath.h>

const class VertexArray
{
private:
	struct VertexInputType
	{
		XMFLOAT4 position;
		XMFLOAT2 tex;
	};
	static const int VERTEX_COUNT = 4;
	static const int INDEX_COUNT = 6;
public:
	VertexArray() = delete;
	VertexArray(VertexArray&) = delete;
	VertexArray(ID3D11Device* device, float width, float height);
	~VertexArray();

	void draw(ID3D11DeviceContext* deviceContext);
private:
	void createVertexBuffer(ID3D11Device* device);
	void createIndexBuffer(ID3D11Device* device);
private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
	float m_Width;
	float m_Height;
};