#pragma once
#include "GameObject.h"

class Submarine : public GameObject
{
public:
	Submarine() = delete;
	Submarine(Submarine&) = delete;
	Submarine(ID3D11Device* device, Texture* texture, )
};