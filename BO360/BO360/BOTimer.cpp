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

	m_frames = 0;
	m_milliSecondsPassed = 0;
	m_offset = 0;
	m_FPS = 0;

	return true;
}

void BOTimer::Tick()
{
	m_totalTimeMS = SDL_GetTicks();
	m_frames++;

	if (m_totalTimeMS - m_offset > 1000)
	{
		m_FPS = m_frames;

		m_offset = m_totalTimeMS;
		m_frames = 0;
	}
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

int BOTimer::FPS()
{
	return m_FPS;
}