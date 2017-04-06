#pragma once
#include <Windows.h>

const class Game
{
public:
	static Game* getGameClass(HINSTANCE instanceHandle, int show);
	static void shutdown();

	bool frame();
private:
	Game(HINSTANCE instanceHandle, int show);
	~Game();
	static Game* m_Game;
};