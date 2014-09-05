#include "Utility.h"
#include "Main.h"

#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* m_window = NULL;
SDL_Surface* m_screenSurface = NULL;
SDL_Surface* m_HelloWorld = NULL;

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		m_window = SDL_CreateWindow("Testing dafunc", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			printf("Window is fucked up!!!!! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			m_screenSurface = SDL_GetWindowSurface(m_window);
		}
	}
	return true;
}
bool loadMedia()
{
	m_HelloWorld = SDL_LoadBMP("test.bmp");
	if (m_HelloWorld == NULL)
	{
		printf("Pic can't be lodaedededed SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}
void close()
{
	SDL_FreeSurface(m_HelloWorld);
	m_HelloWorld = NULL;

	SDL_DestroyWindow(m_window);
	m_window = NULL;

	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!init())
	{
		printf("FAILED TO INIT!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("FAILED TO LOAD IMAGE!\n");
		}
		else
		{
			SDL_BlitSurface(m_HelloWorld, NULL, m_screenSurface, NULL);
			SDL_UpdateWindowSurface(m_window);

		}
	}

	SDL_Delay(40000);
	close();
	return 0;
}