#pragma once
#include "GameObject.h"
#include "SubmarineObserver.h"
#include "GameTimer.h"
#include "Bullet.h"

class Enemy1 : public GameObject
{
public:
	Enemy1() = delete;
	Enemy1(Enemy1&) = delete;
	Enemy1(ID3D11Device* device, Texture* texture, XMFLOAT2 position, SubmarineObserver* observer);
	virtual ~Enemy1();

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