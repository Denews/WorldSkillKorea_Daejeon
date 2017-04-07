#pragma once
#include "GameObject.h"

class Text : public GameObject
{
public:
	enum TextColor
	{
		TEXT_COLOR_BLACK = 0,
		TEXT_COLOR_RED = 1
	};
public:
	Text() = delete;
	Text(Text&);
	Text(LPCSTR string);
	virtual ~Text();

	virtual void update(float deltaTime) override;
	virtual void draw(ID3D11DeviceContext* deviceContext, CXMMATRIX viewOrtho) override;

	virtual void setTextColor(TextColor color);
	virtual char* getText();
	virtual void setText(LPCSTR string);
private:
	TextColor m_Color;
	char* m_String;
};