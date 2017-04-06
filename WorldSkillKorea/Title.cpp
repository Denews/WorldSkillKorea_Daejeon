#include "Title.h"

Title::Title(ID3D11Device* device) :
	m_Texture(new Texture(device, "./Submarine.dds")),
	m_Square(new Square(device, m_Texture, 256, 64))
{

}

Title::~Title()
{
	if (m_Texture)
	{
		delete m_Texture;
		m_Texture = nullptr;
	}
	if (m_Square)
	{
		delete m_Square;
		m_Square = nullptr;
	}
}

void Title::update(float deltaTime)
{

}

void Title::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix)
{
	m_Square->draw(deviceContext, orthoMatrix);
}