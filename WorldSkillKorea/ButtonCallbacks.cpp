#include "ButtonCallbacks.h"
#include "GameState.h"
#include "Stage1.h"
#include "Introduce.h"
#include "HowToPlay.h"
#include "Ranking.h"
#include "Credit.h"

void StartCallback::onSelected()
{
	GameState::curLevel = new Stage1(GameState::graphics->getDevice());
}

void IntroduceCallback::onSelected()
{
	GameState::curLevel = new Introduce(GameState::graphics->getDevice());
}

void HowToplayCallback::onSelected()
{
	GameState::curLevel = new HowToPlay(GameState::graphics->getDevice());
}

void RankingCallback::onSelected()
{
	GameState::curLevel = new Ranking(GameState::graphics->getDevice());
}

void CreditCallback::onSelected()
{
	GameState::curLevel = new Credit(GameState::graphics->getDevice());
}

void QuitCallback::onSelected()
{
	GameState::gameShouldRunning = false;
}