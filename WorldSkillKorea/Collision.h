#pragma once
#include <D3D11.h>
#include <xnamath.h>

class Collision {
public :
	static bool CircleCollision(XMFLOAT2 Spot1, XMFLOAT2 Spot2, float r1, float r2);
	static bool SquareCollision(XMFLOAT2 Spot1, XMFLOAT2 Spot2, XMFLOAT2 Spot3, XMFLOAT2 Spot4);
	static bool CircleSquareCollision(XMFLOAT2 Spot1, XMFLOAT2 Spot2, XMFLOAT2 Circle, float r);
};