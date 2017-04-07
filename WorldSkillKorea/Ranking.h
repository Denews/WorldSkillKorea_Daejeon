#pragma once
#include "GameLevel.h"
#include "Background.h"

class Ranking : public GameLevel {
public:
	Ranking() = delete;
	Ranking(Ranking&) = delete;
	Ranking(ID3D11Device* device);
	virtual ~Ranking();

	virtual void update(float deltaTime) override;
	virtual void draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) override;

private:
	Texture* bgTexture;
	Background* bg;
};