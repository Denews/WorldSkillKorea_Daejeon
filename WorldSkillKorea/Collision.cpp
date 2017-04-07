#include "Collision.h"
#include <xnamath.h>
#include <cmath>

bool Collision::CircleCollision(XMFLOAT2 Spot1, XMFLOAT2 Spot2, float r1, float r2) {
	if (((Spot2.x - Spot1.x)*(Spot2.x - Spot1.x) + (Spot2.y - Spot1.y)*(Spot2.y - Spot1.y)) < (r1+r2)*(r1+r2)) {
		return true;
	}
	else {
		return false;
	}
}

bool Collision::SquareCollision(XMFLOAT2 Spot1, XMFLOAT2 Spot2, XMFLOAT2 Spot3, XMFLOAT2 Spot4) {
	if (Spot1.x > Spot2.x) {
		float temp;
		temp = Spot1.x;
		Spot1.x = Spot2.x;
		Spot2.x = temp;
	}
	if (Spot1.y > Spot2.y) {
		float temp;
		temp = Spot1.y;
		Spot1.y = Spot2.y;
		Spot2.y = temp;
	}
	if (Spot3.x > Spot4.x) {
		float temp;
		temp = Spot1.x;
		Spot1.x = Spot2.x;
		Spot2.x = temp;
	}
	if (Spot3.x > Spot4.x) {
		float temp;
		temp = Spot3.x;
		Spot3.x = Spot4.x;
		Spot4.x = temp;
	}

	float Top1 = Spot2.y;
	float Bottom1 = Spot1.y;
	float Left1 = Spot1.x;
	float Right1 = Spot2.x;

	float Top2 = Spot4.y;
	float Bottom2 = Spot3.y;
	float Left2 = Spot3.x;
	float Right2 = Spot4.x;

	if ( (((Bottom2 < Top1) && (Top1 < Top2)) || ((Bottom2 < Bottom1)&&(Bottom1 < Top2))) && (((Left2 < Right1) && (Right1 < Right2)) || ((Left2 < Left1) && (Left1 < Right2))) ) {
		return true;
	}
	else {
		return false;
	}
}

bool Collision::CircleSquareCollision(XMFLOAT2 Spot1, XMFLOAT2 Spot2, XMFLOAT2 Circle, float r) {
	if (Spot1.x > Spot2.x) {
		float temp;
		temp = Spot1.x;
		Spot1.x = Spot2.x;
		Spot2.x = temp;
	}
	if (Spot1.y > Spot2.y) {
		float temp;
		temp = Spot1.y;
		Spot1.y = Spot2.y;
		Spot2.y = temp;
	}

	float Top = Spot2.y;
	float Bottom = Spot1.y;
	float Left = Spot1.x;
	float Right = Spot2.x;

	if ((Left < Circle.x) && (Circle.x < Right) && ((abs(Circle.y - Top) < r) || (abs(Bottom - Circle.y) < r)) ) {
		return true;
	}
	else if ((Bottom < Circle.y) && (Circle.y < Top) && ((abs(Circle.x - Left) < r) || (abs(Right - Circle.x) < r)) ) {
		return true;
	}

	else if (((Spot1.x - Circle.x) * (Spot1.x - Circle.x) + (Spot1.y - Circle.y) * (Spot1.y - Circle.y)) < r*r) {
		return true;
	}
	
	else if (((Spot2.x - Circle.x) * (Spot2.x - Circle.x) + (Spot1.y - Circle.y) * (Spot1.y - Circle.y)) < r*r) {
		return true;
	}

	else if (((Spot1.x - Circle.x) * (Spot1.x - Circle.x) + (Spot2.y - Circle.y) * (Spot2.y - Circle.y)) < r*r) {
		return true;
	}
	else if (((Spot2.x - Circle.x) * (Spot2.x - Circle.x) + (Spot2.y - Circle.y) * (Spot2.y - Circle.y)) < r*r) {
		return true;
	}
	else {
		return false;
	}

}