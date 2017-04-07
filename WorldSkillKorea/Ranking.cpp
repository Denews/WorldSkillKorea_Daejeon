#include "Ranking.h"
#include "GameState.h"
#include "Title.h"

Ranking::Ranking(ID3D11Device* device) :
	bgTexture(nullptr),
	bg(nullptr)
{
	bgTexture = new Texture(device, "./res/Background/Ranking.dds");
	bg = new Background(device, bgTexture);
}

Ranking::~Ranking() {
	delete bgTexture;
	delete bg;
}

void Ranking::update(float deltaTime) {
	if (GameState::input->getKey(DIK_ESCAPE)) {
		GameState::curLevel = new Title(GameState::graphics->getDevice());
	}
	bg->update(deltaTime);
}

void Ranking::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) {
	bg->draw(deviceContext, orthoMatrix);
}