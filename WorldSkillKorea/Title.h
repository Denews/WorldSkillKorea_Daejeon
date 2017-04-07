#pragma once
#include "GameLevel.h"
#include "Button.h"
#include "Texture.h"
#include "ButtonCallbacks.h"
#include "Background.h"

class Title : public GameLevel
{
public:
	Title() = delete;
	Title(Title&) = delete;
	Title(ID3D11Device* device);
	virtual ~Title();

	virtual void update(float deltaTime) override;
	virtual void draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) override;
private:
	Texture* BackgroundTexture;
	Background* bg;
	Texture** ButtonTextures;
	Texture** FocusedButtonTextures;
	ButtonCallback** ButtonCallbacks;
	Button** Buttons;
	int ButtonIndex;
};