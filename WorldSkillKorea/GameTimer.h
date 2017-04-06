#pragma once
#include <Windows.h>

class GameTimer
{
public:
	GameTimer();
	GameTimer(GameTimer&) = default;
	virtual ~GameTimer() = default;

	virtual float totalTime() const;
	virtual float deltaTime() const;

	virtual void start();
	virtual void stop();
	virtual void resume();
	virtual void reset();
	virtual void tick();
private:
	INT64 m_BaseTime;
	INT64 m_PausedTime;
	INT64 m_StopTime;

	INT64 m_CurTime;
	INT64 m_PrevTime;
	INT64 m_DeltaTime;

	double m_SecondsPerCount;

	bool m_IsStopped;
};