#include <Windows.h>
#include "Game.h"

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstanceHandle, LPSTR commandLine, int nShowCmd)
{
	try 
	{
		Game* game = Game::getGameClass(instanceHandle, nShowCmd);
		bool running = true;

		while (running)
		{
			running = game->Frame();
		}
	}
	catch (char* errTxt)
	{
		MessageBoxA(0, errTxt, 0, 0);
	}
	
	return 0;
}