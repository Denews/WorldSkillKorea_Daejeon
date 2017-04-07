#include "Torpedo.h"

Torpedo::Torpedo(ID3D11Device* device, Texture* texture, XMFLOAT2 position) :
	GameObject(device, texture, 128, 16)
{
	setPosition(position.x, position.y, 3.0f);
}

void Torpedo::update(float deltaTime)
{
	setPosition(getPosition().x + SPEED * deltaTime, getPosition().y, getPosition().z);
}

bool Torpedo::isOutOfView(View* view)
{
	if (getPosition().x < view->getLeft()) return true;
	if (getPosition().x > view->getRight()) return true;
	if (getPosition().y > view->getTop()) return true;
	if (getPosition().y < view->getBottom()) return true;
	return false;
}