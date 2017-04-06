#pragma once
#include "GameLevel.h"
#include "Square.h"

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
	Square* m_Square;
	Texture* m_Texture;
};