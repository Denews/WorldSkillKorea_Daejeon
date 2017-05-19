#pragma once
#include "GameObject.h"
#include "SubmarineObserver.h"
#include "GameTimer.h"
#include "Bullet.h"

class Enemy2 : public GameObject
{
public:
	Enemy2() = delete;
	Enemy2(Enemy2&) = delete;
	Enemy2(ID3D11Device* device, Texture* texture, XMFLOAT2 position, SubmarineObserver* observer);
	virtual ~Enemy2();

	virtual void update(float deltaTime) override;
	virtual void draw(ID3D11DeviceContext* deviceContext, CXMMATRIX viewOrtho) override;
	virtual void act();

	virtual XMFLOAT3 getPosition() const override;
private:
	static const int MAX_BULLET_COUNT = 200;
	static const float BULLET_INTERVAL;
private:

	GameTimer* m_BulletTimer;
	bool m_IsActive;

	SubmarineObserver* m_Observer;

	Texture* m_BulletTexture;
	Bullet** m_Bullets;
	int m_BulletArrayIndex;
};