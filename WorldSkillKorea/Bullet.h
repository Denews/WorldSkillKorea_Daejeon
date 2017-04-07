#pragma once
#include "GameObject.h"
#include "View.h"

class Bullet : public GameObject
{
public:
	Bullet() = delete;
	Bullet(Bullet&) = delete;
	Bullet(ID3D11Device* device, Texture* texture, float speed, XMFLOAT2 position, XMFLOAT2 direction);
	virtual ~Bullet() = default;

	virtual void update(float deltaTime) override;
	virtual bool isOutOfView(View* view);
private:
	float m_Speed;
	XMFLOAT2 m_Direction;
};