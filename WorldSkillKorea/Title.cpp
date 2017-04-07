#include "Title.h"
#include "ImageConstants.h"
#include "ButtonCallbacks.h"
#include "GameState.h"

Title::Title(ID3D11Device* device) :
	ButtonTextures(new Texture*[6]),
	FocusedButtonTextures(new Texture*[6]),
	ButtonCallbacks(new ButtonCallback*[6]),
	Buttons(new Button*[6]),
	ButtonIndex(0)
{
	BackgroundTexture = new Texture(device, "./res/Background/Title.dds");
	bg = new Background(device, BackgroundTexture);

	ButtonCallbacks[0] = new StartCallback();
	ButtonCallbacks[1] = new IntroduceCallback();
	ButtonCallbacks[2] = new HowToplayCallback();
	ButtonCallbacks[3] = new RankingCallback();
	ButtonCallbacks[4] = new CreditCallback();
	ButtonCallbacks[5] = new QuitCallback();

	for (int i = 0; i < 6; i++) {
		ButtonTextures[i] = new Texture(device, ImageConstants::ButtonPaths[i]);
		FocusedButtonTextures[i] = new Texture(device, ImageConstants::FocusedbuttonPaths[i]);
		Buttons[i] = new Button(device, FocusedButtonTextures[i], ButtonTextures[i], ButtonCallbacks[i]);
		Buttons[i]->unfocus();
	}
	Buttons[0]->focus();
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
	bg->update(deltaTime);

	if (GameState::input->getKey(DIK_RIGHTARROW) && ButtonIndex < 5) {
		Buttons[ButtonIndex]->unfocus();
		ButtonIndex++;
		Buttons[ButtonIndex]->focus();
	}
	if (GameState::input->getKey(DIK_LEFTARROW) && ButtonIndex > 0) {
		Buttons[ButtonIndex]->unfocus();
		ButtonIndex--;
		Buttons[ButtonIndex]->focus();
	}

	if (GameState::input->getKey(DIK_NUMPADENTER)) {
		ButtonCallbacks[ButtonIndex]->onSelected();
	}

	for (int i = 0; i < 6; i++) {
		Buttons[i]->update(deltaTime);
	}

}

void Title::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix)
{
	bg->draw(deviceContext, orthoMatrix);
	Buttons[1]->draw(deviceContext, orthoMatrix);
}