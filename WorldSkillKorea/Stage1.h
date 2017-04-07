#pragma once
#include "GameLevel.h"
#include "Background.h"
#include "Texture.h"
#include "Submarine.h"
#include "View.h"

class Stage1 : public GameLevel
{
public:
	Stage1() = delete;
	Stage1(Stage1&) = delete;
	Stage1(ID3D11Device* device);
	virtual ~Stage1();

	virtual void update(float deltaTime) override;
	virtual void draw(ID3D11DeviceContext* deviceContext, CXMMATRIX ortho) override;
private:
	Texture* m_BackgroundTexture;
	Background* m_Background;

	Texture* m_SubmarineTexture[2];
	Submarine* m_Submarine;

	View* m_View;
};