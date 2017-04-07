#pragma once
#include "GameObject.h"
#include "View.h"

class Torpedo : public GameObject
{
public:
	Torpedo() = delete;
	Torpedo(Torpedo&) = delete;
	Torpedo(ID3D11Device* device, Texture* texture, XMFLOAT2 position);
	virtual ~Torpedo() = default;

	virtual void update(float deltaTime) override;
	bool isOutOfView(View* view);

private:
	static const int SPEED = 3000;
};