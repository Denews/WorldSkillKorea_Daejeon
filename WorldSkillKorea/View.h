#pragma once
#include <D3D11.h>
#include <xnamath.h>

const class View
{
public:
	View();
	View(View&);
	View(float x, float y);
	~View() = default;

	void setPosition(float x, float y);
	XMFLOAT2 getPosition() const;

	float getLeft() const;
	float getRight() const;
	float getTop() const;
	float getBottom() const;

	XMMATRIX getViewMatrix() const;
private:
	XMFLOAT2 m_Position;
};