#include "GameState.h"

GameWindow* GameState::window = nullptr;
Graphics* GameState::graphics = nullptr;

void GameState::initialize(HINSTANCE instanceHandle, int show)
{
	if(!window) window = new GameWindow(instanceHandle, show);
	if(!graphics) graphics = new Graphics(window->getWindowHandle());
}

void GameState::shutdown()
{
	if (graphics)
	{
		delete graphics;
		graphics = nullptr;
	}
	if (window)
	{
		delete window;
		window = nullptr;
	}
}