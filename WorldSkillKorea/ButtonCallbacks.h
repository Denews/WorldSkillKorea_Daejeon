#pragma once
#include "Button.h"
#include "Credit.h"
#include "Stage1.h"
#include "Introduce.h"
#include "HowToPlay.h"
#include "Ranking.h"
#include "GameState.h"

class StartCallback : public ButtonCallback
{
public:
	virtual void onSelected() override {
		GameState::curLevel = new Stage1(GameState::graphics->getDevice());
	};
};

class IntroduceCallback : public ButtonCallback
{
public:
	virtual void onSelected() override {
		GameState::curLevel = new Introduce(GameState::graphics->getDevice());
	};
};

class HowToplayCallback : public ButtonCallback
{
public:
	virtual void onSelected() override {
		GameState::curLevel = new HowToPlay(GameState::graphics->getDevice());
	};
};

class RankingCallback : public ButtonCallback
{
public:
	virtual void onSelected() override {
		GameState::curLevel = new Ranking(GameState::graphics->getDevice());
	};
};

class CreditCallback : public ButtonCallback
{
public:
	virtual void onSelected() override {
		GameState::curLevel = new Credit(GameState::graphics->getDevice());
	};
};

class QuitCallback : public ButtonCallback
{
public:
	virtual void onSelected() override {
		GameState::gameShouldRunning = false;
	};
};