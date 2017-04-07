#include "Introduce.h"
#include "GameState.h"
#include "Title.h"

Introduce::Introduce(ID3D11Device* device) : 
	bgTexture(nullptr),
	bg(nullptr)
{
	bgTexture = new Texture(device, "./res/Background/Introduce.dds");
	bg = new Background(device, bgTexture);
}

Introduce::~Introduce() {
	delete bgTexture;
	delete bg;
}

void Introduce::update(float deltaTime) {
	if (GameState::input->getKey(DIK_ESCAPE)) {
		GameState::curLevel = new Title(GameState::graphics->getDevice());
	}
	bg->update(deltaTime);
}

void Introduce::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) {
	bg->draw(deviceContext, orthoMatrix);
}