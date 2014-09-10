#ifndef BOINPUT_H_
#define BOINPUT_H_

#include "BOComponent.h"
#include "SDL.h"

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

};

#endif

