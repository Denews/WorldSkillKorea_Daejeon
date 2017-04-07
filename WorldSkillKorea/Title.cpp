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

	Buttons[0]->setPosition(324.0f - 960.0f, 540.0f - 264.0f, 0.0f);
	Buttons[1]->setPosition(960.0f - 960.0f, 540.0f - 264.0f, 0.0f);
	Buttons[2]->setPosition(1553.0f - 960.0f, 540.0f - 264.0f, 0.0f);
	Buttons[3]->setPosition(324.0f - 960.0f, 0.0f, 0.0f);
	Buttons[4]->setPosition(960.0f - 960.0f, 0.0f, 0.0f);
	Buttons[5]->setPosition(1553.0f - 960.0f, 0.0f, 0.0f);
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
	delete bg;
	delete BackgroundTexture;
}

void Title::update(float deltaTime)
{
	bg->update(deltaTime);

	if (GameState::input->getKeyPressed(DIK_RIGHTARROW) && ButtonIndex < 5) {
		Buttons[ButtonIndex]->unfocus();
		ButtonIndex++;
		Buttons[ButtonIndex]->focus();
	}
	if (GameState::input->getKeyPressed(DIK_LEFTARROW) && ButtonIndex > 0) {
		Buttons[ButtonIndex]->unfocus();
		ButtonIndex--;
		Buttons[ButtonIndex]->focus();
	}
	if (GameState::input->getKeyPressed(DIK_UPARROW) && ButtonIndex > 2) {
		Buttons[ButtonIndex]->unfocus();
		ButtonIndex -= 3;
		Buttons[ButtonIndex]->focus();
	}
	if (GameState::input->getKeyPressed(DIK_DOWNARROW) && ButtonIndex < 3) {
		Buttons[ButtonIndex]->unfocus();
		ButtonIndex += 3;
		Buttons[ButtonIndex]->focus();
	}
	for (int i = 0; i < 6; i++) {
		Buttons[i]->update(deltaTime);
	}
	if (GameState::input->getKeyPressed(DIK_NUMPADENTER)) {
		Buttons[ButtonIndex]->select();
	}

}

void Title::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix)
{
	bg->draw(deviceContext, orthoMatrix);
	for (int i = 0; i < 6; i++) {
		Buttons[i]->draw(deviceContext, orthoMatrix);
	}
}