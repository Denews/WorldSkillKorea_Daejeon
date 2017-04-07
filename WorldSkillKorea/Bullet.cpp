#include "Bullet.h"

Bullet::Bullet(ID3D11Device* device, Texture* texture, float speed, XMFLOAT2 position, XMFLOAT2 direction) :
	GameObject(device, texture, 16, 16),
	m_Direction(direction),
	m_Speed(speed)
{
	setPosition(position.x, position.y, 0.0f);
}

void Bullet::update(float deltaTime)
{
	float x = getPosition().x;
	float y = getPosition().y;
	float dx = m_Direction.x * m_Speed * deltaTime;
	float dy = m_Direction.y * m_Speed * deltaTime;

	setPosition(x + dx, y + dy, getPosition().z);
}

bool Bullet::isOutOfView(View* view)
{
	if (getPosition().x < view->getLeft()) return true;
	if (getPosition().x > view->getRight()) return true;
	if (getPosition().y > view->getTop()) return true;
	if (getPosition().y < view->getBottom()) return true;
	return false;
}