#pragma once
#include <D3D11.h>
#include <xnamath.h>

class GameLevel
{
public:
	virtual ~GameLevel() = default;

	virtual void update(float deltaTime) = 0;
	virtual void draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) = 0;
};