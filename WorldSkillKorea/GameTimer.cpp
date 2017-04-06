#include "GameTimer.h"

GameTimer::GameTimer() :
	m_BaseTime(0),
	m_CurTime(0),
	m_DeltaTime(0),
	m_IsStopped(false),
	m_PausedTime(0),
	m_PrevTime(0),
	m_SecondsPerCount(0),
	m_StopTime(0)
{
	INT64 tickPerSeconds;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER *>(&tickPerSeconds));
	m_SecondsPerCount = 1.0 / tickPerSeconds;
}

float GameTimer::totalTime() const
{
	if (m_IsStopped)
	{
		INT64 totalCount = m_StopTime - m_BaseTime - m_PausedTime;
		return static_cast<float>(totalCount * m_SecondsPerCount);
	}
	else
	{
		INT64 totalCount = m_CurTime - m_BaseTime - m_PausedTime;
		return static_cast<float>(totalCount * m_SecondsPerCount);
	}
}

float GameTimer::deltaTime() const
{
	if (m_IsStopped) return 0.0f;
	else return static_cast<float>(m_DeltaTime * m_SecondsPerCount);
}

void GameTimer::start()
{
	if (!m_IsStopped) return;

	m_IsStopped = false;
	m_BaseTime = m_CurTime;
	m_PausedTime = 0;
}

void GameTimer::stop()
{
	if (m_IsStopped) return;

	m_IsStopped = true;
	m_StopTime = m_CurTime;
}

void GameTimer::resume()
{
	if (!m_IsStopped) return;

	m_IsStopped = false;
	m_PausedTime += m_CurTime - m_StopTime;
}

void GameTimer::reset()
{
	m_BaseTime = m_CurTime;
	m_PausedTime = 0;
}

void GameTimer::tick()
{
	m_PrevTime = m_CurTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(&m_CurTime));
	m_DeltaTime = m_CurTime - m_PrevTime;
}