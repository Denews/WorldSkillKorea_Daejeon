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
	virtual void onSelected() override;
};

class IntroduceCallback : public ButtonCallback
{
public:
	virtual void onSelected() override;
};

class HowToplayCallback : public ButtonCallback
{
public:
	virtual void onSelected() override;
};

class RankingCallback : public ButtonCallback
{
public:
	virtual void onSelected() override;
};

class CreditCallback : public ButtonCallback
{
public:
	virtual void onSelected() override;
};

class QuitCallback : public ButtonCallback
{
public:
	virtual void onSelected() override;
};