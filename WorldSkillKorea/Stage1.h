#pragma once
#include "GameLevel.h"

class Stage1 : public GameLevel
{
public:
	Stage1() = delete;
	Stage1(Stage1&) = delete;
	Stage1(ID3D11Device* device);
	virtual ~Stage1();

	virtual void update(float deltaTime) override;
	virtual void draw(ID3D11DeviceContext* deviceContext, CXMMATRIX ortho);

};