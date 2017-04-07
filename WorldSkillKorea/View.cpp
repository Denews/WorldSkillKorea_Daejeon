#include "View.h"
#include "GameConstants.h"

View::View()
{
	setPosition(0, 0);
}

View::View(View& other)
{
	setPosition(other.getPosition().x, other.getPosition().y);
}

View::View(float x, float y)
{
	setPosition(x, y);
}

void View::setPosition(float x, float y)
{
	m_Position = { x, y };
}

XMFLOAT2 View::getPosition() const
{
	return m_Position;
}

float View::getLeft() const
{
	return m_Position.x + GameConstants::left;
}

float View::getRight() const
{
	return m_Position.x + GameConstants::right;
}

float View::getTop() const
{
	return m_Position.y + GameConstants::top;
}

float View::getBottom() const
{
	return m_Position.y + GameConstants::bottom;
}

XMMATRIX View::getViewMatrix() const
{
	XMVECTOR position = XMVectorSet(m_Position.x, m_Position.y, 0.0f, 1.0f);
	XMVECTOR direction = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	return XMMatrixLookToLH(position, direction, up);
}