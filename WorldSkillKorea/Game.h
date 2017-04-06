#pragma once
#include <Windows.h>

const class Game
{
public:
	static Game* getGameClass(HINSTANCE instanceHandle, int show);
	static void shutdown();

	bool Frame();
private:
	Game(HINSTANCE instanceHandle, int show);
	static Game* m_Game;
};