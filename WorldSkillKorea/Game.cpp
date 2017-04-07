#include "Game.h"
#include "GameState.h"
#include <cstdio>

Game* Game::s_Game = nullptr;

Game::Game(HINSTANCE instanceHandle, int show) :
	m_FrameCounter(0)
{
	GameState::initialize(instanceHandle, show);
}

Game::~Game()
{
	GameState::shutdown();
}

bool Game::frame()
{
	bool result = true;
	GameState::frameTimer->tick();
	m_FrameCounter += 1;
	if (GameState::frameTimer->totalTime() > 1)
	{
		char str[100];
		sprintf_s(str, "FPS : %d, mSPF : %f\n", m_FrameCounter, GameState::frameTimer->totalTime() * 1000 / m_FrameCounter);
		OutputDebugStringA(str);
		GameState::frameTimer->reset();
		m_FrameCounter = 0;
	}
	GameState::window->pollEvents();
	GameState::input->pollInput();

	float delta = GameState::frameTimer->deltaTime();
	if (delta > 0.1) delta = 0.1f;
	GameState::curLevel->update(delta);

	if (GameState::input->getKey(DIK_LALT) && GameState::input->getKey(DIK_F4))
	{
		result = false;
	}

	GameState::graphics->draw();

	if (!GameState::gameShouldRunning)
	{
		result = false;
	}

	if (GameState::window->windowShouldClose())
	{
		result =  false;
	}

	return result;
}

Game* Game::getGameClass(HINSTANCE instanceHandle, int show)
{
	if (s_Game) return s_Game;
	else
	{
		s_Game = new Game(instanceHandle, show);
		return s_Game;
	}
}

void Game::shutdown()
{
	if (s_Game)
	{
		delete s_Game;
		s_Game = nullptr;
	}
}