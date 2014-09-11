#include "BOTimer.h"

BOTimer::BOTimer()
{

}

BOTimer::~BOTimer()
{

}

bool BOTimer::Initialize()
{
	m_totalTimeMS = 0;
	m_deltaTimeMS = 0;
	m_currentTimeStampMS = 0;
	m_previousTimeStampMS = 0;

	return true;
}

void BOTimer::Tick()
{
	m_totalTimeMS = SDL_GetTicks();
}

float BOTimer::GetTotalTimeS()
{
	return ((float)m_totalTimeMS * 0.001f);
}

Uint32 BOTimer::GetTotalTimeMS()
{
	return m_totalTimeMS;
}

Uint32 BOTimer::GetDeltaTime()
{
	// Get current time stamp.
	m_currentTimeStampMS = SDL_GetTicks();

	// Calculate delta time.
	m_deltaTimeMS = m_currentTimeStampMS - m_previousTimeStampMS;

	// Set the current time stamp as the previous.
	m_previousTimeStampMS = m_currentTimeStampMS;

	return m_deltaTimeMS;
}