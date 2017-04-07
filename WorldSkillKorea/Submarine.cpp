#include "Submarine.h"
#include "GameState.h"
#include "GameConstants.h"

Submarine::Submarine(ID3D11Device* device, Texture* normalTexture, Texture* movingTexture) :
	GameObject(device, movingTexture, 512, 32),
	m_NormalTexture(normalTexture),
	m_MovingTexture(movingTexture)
{

}

void Submarine::update(float deltaTime)
{
	float x = getPosition().x;
	float y = getPosition().y;

	float dx = 0;
	float dy = 0;
	if (GameState::input->getKey(DIK_UP)) dy += SPEED * deltaTime;
	if (GameState::input->getKey(DIK_DOWN)) dy -= SPEED * deltaTime;
	if (GameState::input->getKey(DIK_LEFT)) dx -= SPEED * deltaTime;
	if (GameState::input->getKey(DIK_RIGHT)) dx += SPEED * deltaTime;

	if (dx != 0 && dy != 0)
	{
		dx *= 0.70710678;
		dy *= 0.70710678;
	}

	if (dx != 0 || dy != 0)
	{
		setTexture(m_MovingTexture);
	}
	else
	{
		setTexture(m_NormalTexture);
	}

	float l = GameConstants::left;
	float t = GameConstants::top;
	float b = GameConstants::bottom;

	x = XMMax(l, x + dx);
	y = XMMin(XMMax(b, y + dy), t);

	setPosition(x, y, 7.0f);
}

XMFLOAT3 Submarine::getPosition() const
{
	return GameObject::getPosition();
}