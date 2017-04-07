#include "Stage1.h"
#include "GameConstants.h"
#include "GameState.h"

const float Stage1::TORPEDO_INTERVAL = 0.5;

Stage1::Stage1(ID3D11Device* device) :
	m_Backgrounds(),
	m_BackgroundTexture(nullptr),
	m_Submarine(nullptr),
	m_SubmarineTexture(),
	m_View(nullptr),
	m_Torpedos(new Torpedo*[MAX_TORPEDO_COUNT]),
	m_TorpedoArrayIndex(0),
	m_TorpedoTimer(new GameTimer())
{
	m_BackgroundTexture = new Texture(device, "./res/Background/Stage1.dds");
	m_Backgrounds[0] = new Background(device, m_BackgroundTexture);
	m_Backgrounds[1] = new Background(device, m_BackgroundTexture);
	
	m_SubmarineTexture[0] = new Texture(device, "./res/Player/Submarine_2.dds");
	m_SubmarineTexture[1] = new Texture(device, "./res/Player/Submarine.dds");
	m_Submarine = new Submarine(device, m_SubmarineTexture[0], m_SubmarineTexture[1]);

	m_View = new View();

	m_TorpedoTexture = new Texture(device, "./res/Player/Torpedo.dds");

	for (int i = 0; i < MAX_TORPEDO_COUNT; i++)
	{
		m_Torpedos[i] = nullptr;
	}
	m_TorpedoTimer->reset();
	m_TorpedoTimer->start();
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
	delete m_TorpedoTexture;
	for (int i = 0; i < MAX_TORPEDO_COUNT; i++)
	{
		delete m_Torpedos[i];
	}
	delete[] m_Torpedos;
	delete m_TorpedoTimer;
}

void Stage1::update(float deltaTime)
{
	m_TorpedoTimer->tick();
	m_Backgrounds[0]->update(deltaTime);
	m_Backgrounds[1]->update(deltaTime);
	m_Submarine->update(deltaTime);
	
	if (m_Submarine->getPosition().x > m_View->getPosition().x)
	{
		m_View->setPosition(m_Submarine->getPosition().x, 0);
	}
	else if (m_Submarine->getPosition().x < m_View->getLeft())
	{
		m_View->setPosition(m_Submarine->getPosition().x + GameConstants::width / 2, 0);
	}

	m_Backgrounds[0]->setPosition(m_View->getPosition().x - (static_cast<int>(m_View->getPosition().x) % GameConstants::width), 0, 10.4);
	m_Backgrounds[1]->setPosition(m_Backgrounds[0]->getPosition().x + GameConstants::width, 0, 10.4);

	if (GameState::input->getKey(DIK_Z) && m_TorpedoTimer->totalTime() > TORPEDO_INTERVAL)
	{
		Torpedo* torpedo = new Torpedo(GameState::graphics->getDevice(), m_TorpedoTexture, { m_Submarine->getPosition().x, m_Submarine->getPosition().y });
		while (m_Torpedos[m_TorpedoArrayIndex]) m_TorpedoArrayIndex = (m_TorpedoArrayIndex + 1) % MAX_TORPEDO_COUNT;
		m_Torpedos[m_TorpedoArrayIndex] = torpedo;
		m_TorpedoTimer->reset();
	}

	for (int i = 0; i < MAX_TORPEDO_COUNT; i++)
	{
		if (m_Torpedos[i])
		{
			m_Torpedos[i]->update(deltaTime);
			if (m_Torpedos[i]->isOutOfView(m_View))
			{
				delete m_Torpedos[i];
				m_Torpedos[i] = nullptr;
			}
		}
	}
}

void Stage1::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX ortho)
{
	XMMATRIX viewOrtho = m_View->getViewMatrix() * ortho;

	m_Backgrounds[0]->draw(deviceContext, viewOrtho);
	m_Backgrounds[1]->draw(deviceContext, viewOrtho);
	m_Submarine->draw(deviceContext, viewOrtho);

	for (int i = 0; i < MAX_TORPEDO_COUNT; i++)
	{
		if (m_Torpedos[i])
		{
			m_Torpedos[i]->draw(deviceContext, viewOrtho);
		}
	}
}