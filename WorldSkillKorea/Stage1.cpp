#include "Stage1.h"
#include "GameConstants.h"

Stage1::Stage1(ID3D11Device* device) :
	m_Backgrounds(),
	m_BackgroundTexture(nullptr),
	m_Submarine(nullptr),
	m_SubmarineTexture(),
	m_View(nullptr)
{
	m_BackgroundTexture = new Texture(device, "./res/Background/Stage1.dds");
	m_Backgrounds[0] = new Background(device, m_BackgroundTexture);
	m_Backgrounds[1] = new Background(device, m_BackgroundTexture);
	
	m_SubmarineTexture[0] = new Texture(device, "./res/Player/Submarine_2.dds");
	m_SubmarineTexture[1] = new Texture(device, "./res/Player/Submarine.dds");
	m_Submarine = new Submarine(device, m_SubmarineTexture[0], m_SubmarineTexture[1]);

	m_View = new View();
}

Stage1::~Stage1()
{
	delete m_Backgrounds[0];
	delete m_Backgrounds[1];
	delete m_BackgroundTexture;
	delete m_Submarine;
	delete m_SubmarineTexture[0];
	delete m_SubmarineTexture[1];
	delete m_View;
}

void Stage1::update(float deltaTime)
{
	m_Backgrounds[0]->update(deltaTime);
	m_Backgrounds[1]->update(deltaTime);
	m_Submarine->update(deltaTime);
	
	if (m_Submarine->getPosition().x > m_View->getRight())
	{
		m_View->setPosition(m_Submarine->getPosition().x - GameConstants::width / 2, 0);
	}
	else if (m_Submarine->getPosition().x < m_View->getLeft())
	{
		m_View->setPosition(m_Submarine->getPosition().x + GameConstants::width / 2, 0);
	}

	m_Backgrounds[0]->setPosition(static_cast<int>(m_View->getPosition().x) % GameConstants::width, 0, 10.4);
	m_Backgrounds[1]->setPosition(m_Backgrounds[0]->getPosition().x + GameConstants::width, 0, 10.4);
}

void Stage1::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX ortho)
{
	XMMATRIX viewOrtho = m_View->getViewMatrix() * ortho;

	m_Backgrounds[0]->draw(deviceContext, viewOrtho);
	m_Backgrounds[1]->draw(deviceContext, viewOrtho);
	m_Submarine->draw(deviceContext, viewOrtho);
}