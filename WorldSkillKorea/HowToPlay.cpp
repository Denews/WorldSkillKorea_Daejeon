#include "HowToPlay.h"
#include "GameState.h"
#include "Title.h"

HowToPlay::HowToPlay(ID3D11Device* device) :
	bgTexture(nullptr),
	bg(nullptr)
{
	bgTexture = new Texture(device, "./res/Background/HowToPlay.dds");
	bg = new Background(device, bgTexture);
}

HowToPlay::~HowToPlay() {
	delete bgTexture;
	delete bg;
}

void HowToPlay::update(float deltaTime) {
	if (GameState::input->getKey(DIK_ESCAPE)) {
		GameState::curLevel = new Title(GameState::graphics->getDevice());
	}
	bg->update(deltaTime);
}

void HowToPlay::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) {
	bg->draw(deviceContext, orthoMatrix);
}