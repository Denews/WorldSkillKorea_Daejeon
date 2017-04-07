#pragma once
#include "GameWindow.h"
#include "Graphics.h"
#include "GameTimer.h"
#include "Input.h"
#include "GameLevel.h"

const class GameState
{
public:
	static GameWindow* window;
	static Graphics* graphics;
	static GameTimer* frameTimer;
	static Input* input;
	static GameLevel* curLevel;
	static bool gameShouldRunning;
public:
	static void initialize(HINSTANCE instanceHandle, int show);
	static void shutdown();
private:
	GameState() = default;
};