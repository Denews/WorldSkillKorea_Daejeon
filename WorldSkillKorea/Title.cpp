#include "Title.h"
#include "ImageConstants.h"


Title::Title(ID3D11Device* device) :
	ButtonTextures(new Texture*[6]),
	FocusedButtonTextures(new Texture*[6]),
	ButtonCallbacks(new ButtonCallback*[6]),
	Buttons(new Button*[6])
{
	for (int i = 0; i < 6; i++) {
		ButtonTextures[i] = new Texture(device, ImageConstants::ButtonPaths[i]);
		FocusedButtonTextures[i] = new Texture(device, ImageConstants::FocusedbuttonPaths[i]);
		ButtonCallbacks[i] = new ButtonCallback();
		Buttons[i] = new Button(device, FocusedButtonTextures[i], ButtonTextures[i], ButtonCallbacks[i]);
	}
}

Title::~Title()
{
	for (int i = 0; i < 6; i++) {
		delete ButtonTextures[i];
		delete FocusedButtonTextures[i];
		delete ButtonCallbacks[i];
		delete Buttons[i];
	}
	delete[] ButtonTextures;
	delete[] FocusedButtonTextures;
	delete[] ButtonCallbacks;
	delete[] Buttons;
}

void Title::update(float deltaTime)
{
}

void Title::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix)
{
}