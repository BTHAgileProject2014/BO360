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

	Uint32 GetTotalTimeMS();
	float GetTotalTimeS();

	Uint32 GetDeltaTime();

	int FPS();

private:
	Uint32 m_totalTimeMS;

	Uint32 m_deltaTimeMS;
	Uint32 m_currentTimeStampMS;
	Uint32 m_previousTimeStampMS;

	int m_frames;
	int m_FPS;
	Uint32 m_milliSecondsPassed;
	Uint32 m_offset;
};
#endif