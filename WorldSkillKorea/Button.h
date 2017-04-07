#pragma once
#include "GameObject.h"

class ButtonCallback
{
public:
	virtual void onSelected() = 0;
};

class Button : GameObject
{
public:
	Button() = delete;
	Button(Button&) = delete;
	Button(ID3D11Device* device, Texture* focusedTexture, Texture* unfocusedTexture, ButtonCallback* callback, float width, float height);
	virtual ~Button() = default;

	virtual void focus();
	virtual void unfocus();
	virtual void select();

	virtual void update(float deltaTime) override {};

	virtual void setPosition(float x, float y, float z) override;
	virtual XMFLOAT3 getPosition() const override;

private:
	Texture* m_FocusedTexture;
	Texture* m_UnfocusedTexture;
	bool m_Isfocused;
	ButtonCallback* m_Callback;
};