#pragma once
#include "GameLevel.h"
#include "Background.h"

class Credit : public GameLevel {
public:
	Credit() = delete;
	Credit(Credit&) = delete;
	Credit(ID3D11Device* device);
	virtual ~Credit();

	virtual void update(float deltaTime) override;
	virtual void draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) override;

private:
	Texture* bgTexture;
	Background* bg;
};