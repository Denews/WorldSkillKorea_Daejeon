#pragma once
#include "GameLevel.h"
#include "Background.h"
#include "Texture.h"

class Introduce : public GameLevel {
public :
	Introduce() = delete;
	Introduce(Introduce&) = delete;
	Introduce(ID3D11Device* device);
	virtual ~Introduce();

	virtual void update(float deltaTime) override;
	virtual void draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) override;

private :
	Texture* bgTexture;
	Background* bg;
};