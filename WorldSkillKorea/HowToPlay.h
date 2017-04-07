#pragma once
#include "GameLevel.h"

class HowToPlay : public GameLevel {
public:
	HowToPlay() = delete;
	HowToPlay(HowToPlay&) = delete;
	HowToPlay(ID3D11Device* device);
	virtual ~HowToPlay();

	virtual void update(float deltaTime) override;
	virtual void draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) override;

private:
};