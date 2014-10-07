#include "BOWindow.h"

BOWindow::BOWindow()
{

}

BOWindow::~BOWindow()
{

}

bool BOWindow::Initialize()
{
	return Initialize("", 800, 600);
}

bool BOWindow::Initialize(std::string p_windowText, int p_windowWidth, int p_windowHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) > 0)
	{
#ifdef DEBUG
		std::cout << "SDL_Init() call failed in BOWindow::Initialize()";
#endif
		return false;
	}

	m_sdlWindow = SDL_CreateWindow(p_windowText.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_windowWidth, p_windowHeight, SDL_WINDOW_SHOWN);
	if (m_sdlWindow == NULL)
	{
#ifdef DEBUG
		std::cout << "SDL_CreateWindow() failed in BOWindow::Initialize()";
#endif
		return false;
	}

	return true;
}

void BOWindow::Shutdown()
{
	SDL_DestroyWindow(m_sdlWindow);
	SDL_Quit();
}

void BOWindow::SetWindowText(std::string p_windowText)
{
	SDL_SetWindowTitle(m_sdlWindow, p_windowText.c_str());
}

SDL_Window* BOWindow::GetUnderlyingSDLWindow()
{
	return m_sdlWindow;
}