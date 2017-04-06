#include "Game.h"
#include "GameState.h"

Game* Game::m_Game = nullptr;

Game::Game(HINSTANCE instanceHandle, int show)
{
	GameState::initialize(instanceHandle, show);
}

Game::~Game()
{

}

bool Game::frame()
{
	bool result = true;
	GameState::window->pollEvents();

	GameState::graphics->draw();

	if (GameState::window->windowShouldClose())
	{
		result =  false;
	}

	return result;
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
		GameState::shutdown();
		delete m_Game;
	}
}