#include "Triangle.h"

Triangle::Triangle(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vbd;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.ByteWidth = sizeof(float) * 4 * 3;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	vbd.Usage = D3D11_USAGE_DEFAULT;

	float vertices[3][4] = { { 0.0f, 1.0f, 0.5f, 1.0f },{ 1.0f, -1.0f, 0.5f, 1.0f },{ -1.0f, -1.0f, 0.5f, 1.0f } };
	D3D11_SUBRESOURCE_DATA vrd;
	vrd.pSysMem = static_cast<void *>(vertices);
	vrd.SysMemPitch = 0;
	vrd.SysMemSlicePitch = 0;

	device->CreateBuffer(&vbd, &vrd, &m_VertexBuffer);

	D3D11_BUFFER_DESC ibd;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.ByteWidth = sizeof(UINT) * 3;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;

	UINT indices[3] = { 0, 1, 2 };
	D3D11_SUBRESOURCE_DATA ird;
	ird.pSysMem = static_cast<void *>(indices);
	ird.SysMemPitch = 0;
	ird.SysMemSlicePitch = 0;

	device->CreateBuffer(&ibd, &ird, &m_IndexBuffer);
}

void Triangle::draw(ID3D11DeviceContext *deviceContext)
{
	UINT stride = sizeof(float) * 4;
	UINT offset = 0;

	deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	deviceContext->DrawIndexed(3, 0, 0);
}