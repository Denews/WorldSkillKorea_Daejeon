#include "VertexArray.h"

VertexArray::VertexArray(ID3D11Device* device, float width, float height) :
	m_VertexBuffer(nullptr),
	m_IndexBuffer(nullptr),
	m_Width(width),
	m_Height(height)
{
	createVertexBuffer(device);
	createIndexBuffer(device);
}

VertexArray::~VertexArray()
{
	if (m_VertexBuffer)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = nullptr;
	}
	if (m_IndexBuffer)
	{
		m_IndexBuffer->Release();
		m_IndexBuffer = nullptr;
	}
}

void VertexArray::draw(ID3D11DeviceContext* deviceContext)
{
	UINT stride = sizeof(VertexInputType);
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, offset);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->DrawIndexed(INDEX_COUNT, 0, 0);
}

void VertexArray::createVertexBuffer(ID3D11Device* device)
{
	VertexInputType vertices[VERTEX_COUNT];
	vertices[0].position = { -0.5f, 0.5f, 0.5f, 1.0f };
	vertices[0].color = { 1.0f, 0.0f, 0.0f, 0.0f };

	vertices[1].position = { 0.5f, 0.5f, 0.5f, 1.0f };
	vertices[1].color = { 1.0f, 0.0f, 0.0f, 0.0f };

	vertices[2].position = { 0.5f, -0.5f, 0.5f, 1.0f };
	vertices[2].color = { 1.0f, 0.0f, 0.0f, 0.0f };

	vertices[3].position = { -0.5f, -0.5f, 0.5f, 1.0f };
	vertices[3].color = { 1.0f, 0.0f, 0.0f, 0.0f };

	D3D11_BUFFER_DESC vbd;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.ByteWidth = sizeof(VertexInputType) * VERTEX_COUNT;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	vbd.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA vrd;
	vrd.pSysMem = static_cast<void *>(vertices);
	vrd.SysMemPitch = 0;
	vrd.SysMemSlicePitch = 0;

	device->CreateBuffer(&vbd, &vrd, &m_VertexBuffer);
}

void VertexArray::createIndexBuffer(ID3D11Device* device)
{
	UINT indices[INDEX_COUNT] = { 0, 1, 2, 0, 2, 3 };
	D3D11_BUFFER_DESC ibd;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.ByteWidth = sizeof(UINT) * INDEX_COUNT;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA ird;
	ird.pSysMem = static_cast<void *>(indices);
	ird.SysMemPitch = 0;
	ird.SysMemSlicePitch = 0;

	device->CreateBuffer(&ibd, &ird, &m_IndexBuffer);
}