#include "Button.h"

Button::Button(ID3D11Device* device, Texture* focusedTexture, Texture* unfocusedTexture,
	ButtonCallback* callback, float width, float height) :
	GameObject(device, unfocusedTexture, width, height),
	m_FocusedTexture(focusedTexture),
	m_UnfocusedTexture(unfocusedTexture),
	m_Isfocused(false),
	m_Callback(callback)
{

}

void Button::focus()
{
	m_Isfocused = true;
	setTexture(m_FocusedTexture);
}

void Button::unfocus()
{
	m_Isfocused = false;
	setTexture(m_UnfocusedTexture);
}

void Button::select()
{
	m_Callback->onSelected();
}

void Button::setPosition(float x, float y, float z)
{
	GameObject::setPosition(x, y, z);
}

XMFLOAT3 Button::getPosition() const
{
	return GameObject::getPosition();
}