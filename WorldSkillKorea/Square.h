#pragma once
#include "GameObject.h"

class Square : public GameObject
{
public:
	Square(ID3D11Device* device, Texture* texture, float width, float height);
	virtual ~Square() = default;

	virtual void update(float deltaTime) override {};
};