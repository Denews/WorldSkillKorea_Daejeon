#include "Game.h"
#include "GameState.h"

Game* Game::m_Game = nullptr;

Game::Game(HINSTANCE instanceHandle, int show)
{
	GameState::window = new GameWindow(instanceHandle, show);
}

bool Game::Frame()
{
	GameState::window->pollEvents();
	if (GameState::window->windowShouldClose())
	{
		return false;
	}
	else
	{
		return true;
	}
}

Game* Game::getGameClass(HINSTANCE instanceHandle, int show)
{
	if (m_Game) return m_Game;
	else
	{
		m_Game = new Game(instanceHandle, show);
		return m_Game;
	}
}

void Game::shutdown()
{
	if (m_Game)
	{
		delete GameState::window;
		delete m_Game;
	}
}