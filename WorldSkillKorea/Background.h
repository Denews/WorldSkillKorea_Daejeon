#pragma once
#include "GameObject.h"

class Background : public GameObject
{
public:
	Background() = delete;
	Background(Background&) = delete;
	Background(ID3D11Device* device, Texture* texture);
	virtual ~Background() = default;

	virtual void update(float deltaTime) override {};
};