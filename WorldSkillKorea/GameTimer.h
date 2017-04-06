#pragma once
#include <Windows.h>

class GameTimer
{
public:
	GameTimer();
	GameTimer(GameTimer&);
	~GameTimer();

	float totalTime() const;
	float deltaTime() const;

	void Start();
	void Stop();
	void Reset();
	void Tick();
private:
	INT64 m_StartTime;
	INT64 m_StoppedTime;
	INT64 m_CurTime;
	INT64 m_PrevTime;
	INT64 m_DeltaTime;

	double m_SecondsPerCount;

	bool m_IsStopped;
};