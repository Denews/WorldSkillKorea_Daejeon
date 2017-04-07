#include "Credit.h"
#include "GameState.h"
#include "Title.h"

Credit::Credit(ID3D11Device* device) :
	bgTexture(nullptr),
	bg(nullptr)
{
	bgTexture = new Texture(device, "./res/Background/Credit.dds");
	bg = new Background(device, bgTexture);
}

Credit::~Credit() {
	delete bgTexture;
	delete bg;
}

void Credit::update(float deltaTime) {
	if (GameState::input->getKey(DIK_ESCAPE)) {
		GameState::curLevel = new Title(GameState::graphics->getDevice());
	}
	bg->update(deltaTime);
}

void Credit::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) {
	bg->draw(deviceContext, orthoMatrix);
}