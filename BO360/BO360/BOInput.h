#ifndef BOINPUT_H_
#define BOINPUT_H_

#include "BOComponent.h"
#include "SDL.h"
#include "BOPublisher.h"
#include "BOUtility.h"

class BOInput : BOComponent
{
public:
	BOInput();
	~BOInput();

	bool Initialize();
	void Shutdown();

	// Handles SDL_Events
	bool Update();

private:
	BOPublisher m_publisher;
	bool m_buttonsPressed[10];
};
#endif