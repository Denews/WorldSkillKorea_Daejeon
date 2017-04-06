#pragma once
#include "GameWindow.h"
#include "Graphics.h"

const class GameState
{
public:
	static GameWindow* window;
	static Graphics* graphics;
public:
	static void initialize(HINSTANCE instanceHandle, int show);
	static void shutdown();
private:
	GameState() = default;
};