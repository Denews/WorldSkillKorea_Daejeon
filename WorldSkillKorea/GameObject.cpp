#include "GameObject.h"

GameObject::GameObject(ID3D11Device* device, Texture* texture, float width, float height) :
	m_VertexArray(new VertexArray(device, width, height)),
	m_Texture(texture),
	m_MatrixBuffer(nullptr),
	m_Position({ 0.0f, 0.0f, 0.0f }),
	m_Scale({ 1.0f, 1.0f }),
	m_Angle(0.0f)
{
	createMatrixBuffer(device);
}

GameObject::~GameObject()
{
	if (m_VertexArray)
	{
		delete m_VertexArray;
		m_VertexArray = nullptr;
	}
	if (m_MatrixBuffer)
	{
		m_MatrixBuffer->Release();
		m_MatrixBuffer = nullptr;
	}
}

void GameObject::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX viewOrtho)
{
	fillMatrixBuffer(deviceContext, viewOrtho);

	m_Texture->bind(deviceContext);

	deviceContext->VSSetConstantBuffers(0, 1, &m_MatrixBuffer);
	m_VertexArray->draw(deviceContext);
}

void GameObject::createMatrixBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC mbd;
	mbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	mbd.ByteWidth = sizeof(XMFLOAT4X4);
	mbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	mbd.MiscFlags = 0;
	mbd.StructureByteStride = 0;
	mbd.Usage = D3D11_USAGE_DYNAMIC;

	HRESULT hr = device->CreateBuffer(&mbd, nullptr, &m_MatrixBuffer);
	if (FAILED(hr))
	{
		throw "Create MatrixBuffer Failed";
	}
}

void GameObject::fillMatrixBuffer(ID3D11DeviceContext* deviceContext, CXMMATRIX viewOrtho)
{
	D3D11_MAPPED_SUBRESOURCE mmr;
	deviceContext->Map(m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mmr);
	
	XMMATRIX translate = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX rotate = XMMatrixRotationAxis(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), m_Angle);
	XMMATRIX scale = XMMatrixScaling(m_Scale.x, m_Scale.y, 1.0f);

	XMMATRIX world = scale * rotate * translate;
	XMMATRIX worldviewOrtho = world * viewOrtho;

	XMStoreFloat4x4(static_cast<XMFLOAT4X4 *>(mmr.pData), XMMatrixTranspose(worldviewOrtho));

	deviceContext->Unmap(m_MatrixBuffer, 0);
}

void GameObject::setPosition(float x, float y, float z)
{
	m_Position = { x,y,z };
}
XMFLOAT3 GameObject::getPosition() const
{
	return m_Position;
}

void GameObject::setAngle(float angle)
{
	m_Angle = angle;
}
float GameObject::getAngle() const
{
	return m_Angle;
}

void GameObject::setScale(float x, float y)
{
	m_Scale = { x, y };
}
XMFLOAT2 GameObject::getScale() const
{
	return m_Scale;
}

void GameObject::setTexture(Texture* texture)
{
	m_Texture = texture;
}