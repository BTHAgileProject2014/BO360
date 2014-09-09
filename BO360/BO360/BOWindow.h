#ifndef BOWINDOW_H_
#define BOWINDOW_H_

#include "BOComponent.h"
#include <SDL.h>
#include <string>
#include <stdio.h>

class BOWindow : BOComponent
{
public:
	BOWindow();
	~BOWindow();

	bool Initialize();
	bool Initialize(std::string p_windowText, int p_windowWidth, int p_windowHeight);
	void SetWindowText(std::string p_windowText);

	void Shutdown();

private:
	SDL_Window* m_sdlWindow;
};
#endif