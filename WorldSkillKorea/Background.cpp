#include "Background.h"
#include "GameConstants.h"

Background::Background(ID3D11Device* device, Texture* texture) :
	GameObject(device, texture, GameConstants::width, GameConstants::height)
{
	setPosition(0.0f, 0.0f, 10.5f);
}