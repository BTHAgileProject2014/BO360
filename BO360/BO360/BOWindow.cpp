#include "BOWindow.h"


BOWindow::BOWindow()
{
}


BOWindow::~BOWindow()
{
}


bool BOWindow::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		return false;
	}

	m_sdlWindow = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (m_sdlWindow == NULL)
	{
		return false;
	}

	return true;
}

void BOWindow::Shutdown()
{
	SDL_DestroyWindow(m_sdlWindow);
	SDL_Quit();
}