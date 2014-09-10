#include "BOInput.h"
#include <iostream>

BOInput::BOInput()
{
}


BOInput::~BOInput()
{
}

bool BOInput::Initialize()
{
	return true;
}

void BOInput::Shutdown()
{

}

bool BOInput::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				// Quit
				return false;
			}

			case SDL_KEYDOWN:
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_LEFT:
					{
						std::cout << "LEFT is pressed\n";
						break;
					}

					case SDLK_RIGHT:
					{
						std::cout << "RIGHT is pressed\n";
						break;
					}

					case SDLK_SPACE:
					{
						std::cout << "SPACE is pressed\n";
						break;
					}

					case SDLK_ESCAPE:
					{
						// Quit using the Escape key
						return false;
						break;
					}
				}
				break;
			}

			case SDL_KEYUP:
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_LEFT:
					{
						std::cout << "LEFT is released\n";
						break;
					}

					case SDLK_RIGHT:
					{
						std::cout << "RIGHT is released\n";
						break;
					}

					case SDLK_SPACE:
					{
						std::cout << "SPACE is released\n";
						break;
					}
				}
				break;
			}
		}
	}
	// Keep the program running
	return true;
}

