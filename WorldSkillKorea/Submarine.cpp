#include "Submarine.h"
#include "GameState.h"

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

	if(dx != 0 || dy != 0)
}

XMFLOAT3 Submarine::getPosition() const
{
	return GameObject::getPosition();
}