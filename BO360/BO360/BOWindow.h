#ifndef BOWINDOW_H_
#define BOWINDOW_H_

#include "BOComponent.h"
#include <SDL.h>

class BOWindow : BOComponent
{
public:
	BOWindow();
	~BOWindow();

	bool Initialize();
	void Shutdown();

private:
	SDL_Window* m_sdlWindow;
};
#endif