#include "Enemy1.h"
#include "GameState.h"

const float Enemy1::BULLET_INTERVAL = 0.1;

Enemy1::Enemy1(ID3D11Device* device, Texture* texture, XMFLOAT2 position, SubmarineObserver* observer) :
	GameObject(device, texture, 128, 64),
	m_BulletTimer(new GameTimer()),
	m_IsActive(false),
	m_Bullets(new Bullet*[MAX_BULLET_COUNT]),
	m_BulletTexture(new Texture(device, "./res/Enemy/Bullet_G.dds")),
	m_BulletArrayIndex(0),
	m_Observer(observer)
{
	setPosition(position.x, position.y, 8.0f);
	m_BulletTimer->reset();
	m_BulletTimer->start();

	for (int i = 0; i < MAX_BULLET_COUNT; i++)
	{
		m_Bullets[i] = nullptr;
	}
}

Enemy1::~Enemy1()
{
	for (int i = 0; i < MAX_BULLET_COUNT; i++)
	{
		if (m_Bullets[i])
		{
			delete m_Bullets[i];
		}
	}
	delete[] m_Bullets;
	delete m_BulletTexture;
	delete m_BulletTimer;
}

void Enemy1::update(float deltaTime)
{
	m_BulletTimer->tick();

	if (m_IsActive)
	{
		setPosition(getPosition().x - 0.5, getPosition().y, getPosition().z);
		if (m_BulletTimer->totalTime() > BULLET_INTERVAL)
		{
			while (m_Bullets[m_BulletArrayIndex]) m_BulletArrayIndex = (m_BulletArrayIndex + 1) % MAX_BULLET_COUNT;
			XMFLOAT3 p = m_Observer->getPosition();
			XMVECTOR pv = XMLoadFloat3(&p);
			XMVectorSetZ(pv, 0);
			XMVectorSetW(pv, 0);
			XMFLOAT3 b = getPosition();
			XMVECTOR bv = XMLoadFloat3(&b);
			XMVectorSetZ(bv, 0);
			XMVectorSetW(bv, 0);
			XMVECTOR dir = XMVector2Normalize(pv - bv);
			XMFLOAT2 d;
			XMStoreFloat2(&d, dir);
			
			m_Bullets[m_BulletArrayIndex] = new Bullet(GameState::graphics->getDevice(), m_BulletTexture, 
				1000.0f, { getPosition().x, getPosition().y }, d, m_Observer);
			m_BulletTimer->reset();
		}

		for (int i = 0; i < MAX_BULLET_COUNT; i++)
		{
			if (m_Bullets[i])
			{
				m_Bullets[i]->update(deltaTime);
			}
		}
	}
}

void Enemy1::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX viewOrtho)
{
	GameObject::draw(deviceContext, viewOrtho);

	if (m_IsActive)
	{

		for (int i = 0; i < MAX_BULLET_COUNT; i++)
		{
			if (m_Bullets[i])
			{
				m_Bullets[i]->draw(deviceContext, viewOrtho);
			}
		}
	}
}

void Enemy1::act()
{
	m_IsActive = true;
}

XMFLOAT3 Enemy1::getPosition() const
{
	return GameObject::getPosition();
}