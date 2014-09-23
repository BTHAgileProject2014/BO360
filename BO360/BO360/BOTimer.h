#ifndef BOTIMER_H_
#define BOTIMER_H_

#include "SDL.h"
#include "BOComponent.h"

class BOTimer : public BOComponent
{
public:
	BOTimer();
	~BOTimer();

	bool Initialize();
	void Tick();

	double GetTotalTimeMS();
	double GetTotalTimeS();

	double GetDeltaTime();

	int FPS();

private:
	Uint64 m_totalTime;
	double m_deltaTimeS;

	double m_averageFps;


	Uint64 m_startTimeStamp;
	Uint64 m_currentTimeStamp;
	Uint64 m_previousTimeStamp;
	Uint64 m_clocksPerSecond;
	double m_secondsPerClock;

	int m_frames;
	int m_FPS;
	Uint64 m_milliSecondsPassed;
	Uint64 m_offset;
};
#endif