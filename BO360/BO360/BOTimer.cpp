#include "BOTimer.h"

BOTimer::BOTimer()
{

}

BOTimer::~BOTimer()
{

}

bool BOTimer::Initialize()
{
	m_startTimeStamp = SDL_GetPerformanceCounter();
	m_totalTime = m_startTimeStamp;
	//m_deltaTime = 0;
	m_currentTimeStamp = m_startTimeStamp;
	m_previousTimeStamp = m_startTimeStamp;

	m_clocksPerSecond = SDL_GetPerformanceFrequency();
	m_secondsPerClock = 1.0 / m_clocksPerSecond;

	m_averageFps = 1.0f;
	m_frames = 0;
	m_milliSecondsPassed = 0;
	m_offset = 0;
	m_FPS = 0;

	return true;
}

void BOTimer::Tick()
{
	// Update the total time
	m_totalTime = SDL_GetPerformanceCounter() - m_startTimeStamp;

	// Update m_deltaTimeS
	m_currentTimeStamp = SDL_GetPerformanceCounter();
	Uint64 deltaTime = m_currentTimeStamp - m_previousTimeStamp;
	m_previousTimeStamp = m_currentTimeStamp;
	m_deltaTimeS = deltaTime * m_secondsPerClock;
	if (m_averageFps < 1.0f)
	{
		m_averageFps = 1.0f;
	}
	double scaleFactor = 1.0f / m_averageFps;
	m_averageFps = scaleFactor * (m_clocksPerSecond / (double)deltaTime) + (1.0 - scaleFactor) * m_averageFps;
    //std::cout << m_averageFps << std::endl;
}

double BOTimer::GetTotalTimeS()
{
	return ((double)m_totalTime * m_secondsPerClock);
}

double BOTimer::GetTotalTimeMS()
{
	return m_totalTime * m_secondsPerClock * 10e3;
}

double BOTimer::GetDeltaTime()
{
	return m_deltaTimeS;
}

int BOTimer::FPS()
{
	return (int)m_averageFps;
}