#pragma once
#include "GameLevel.h"
#include "Background.h"
#include "Texture.h"
#include "Submarine.h"
#include "View.h"
#include "Torpedo.h"
#include "GameTimer.h"
#include "Enemy1.h"

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
	static const int MAX_TORPEDO_COUNT = 100;
	static const float TORPEDO_INTERVAL;
private:
	Texture* m_BackgroundTexture;
	Background* m_Backgrounds[2];

	Texture* m_SubmarineTexture[2];
	Submarine* m_Submarine;

	View* m_View;

	Texture* m_TorpedoTexture;
	Torpedo** m_Torpedos;
	int m_TorpedoArrayIndex;
	GameTimer* m_TorpedoTimer;

	Enemy1** m_Enemy1s;

	Texture* m_Monster1Texture;
};