#include "GameState.h"

GameWindow* GameState::window = nullptr;
Graphics* GameState::graphics = nullptr;
GameTimer* GameState::frameTimer = nullptr;
Input* GameState::input = nullptr;

void GameState::initialize(HINSTANCE instanceHandle, int show)
{
	if(!window) window = new GameWindow(instanceHandle, show);
	if(!graphics) graphics = new Graphics(window->getWindowHandle());
	if (!input) input = new Input(instanceHandle, window->getWindowHandle());
	if (!frameTimer) frameTimer = new GameTimer();

	frameTimer->reset();
	frameTimer->start();
}

void GameState::shutdown()
{
	if (frameTimer)
	{
		delete frameTimer;
		frameTimer = nullptr;
	}
	if (input)
	{
		delete input;
		input = nullptr;
	}
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