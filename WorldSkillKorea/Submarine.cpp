#include "Submarine.h"
#include "GameState.h"
#include "GameConstants.h"

Submarine::Submarine(ID3D11Device* device, Texture* texture) :
	GameObject(device, texture, 512, 32)
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

	float l = GameConstants::left;
	float r = GameConstants::right;
	float t = GameConstants::top;
	float b = GameConstants::bottom;

	x = XMMin(XMMax(l, x + dx), r);
	y = XMMin(XMMax(b, y + dy), t);

	setPosition(x, y, 1.0f);
}

XMFLOAT3 Submarine::getPosition() const
{
	return GameObject::getPosition();
}