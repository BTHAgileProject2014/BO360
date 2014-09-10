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
	m_publisher.Initialize();
	return true;
}

void BOInput::Shutdown()
{
	m_publisher.Shutdown();
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
					case SDLK_UP:
					{
						m_publisher.Notify(upArrow, true);
						std::cout << "UP is pressed\n";
						break;
					}

					case SDLK_DOWN:
					{
						m_publisher.Notify(downArrow, true);
						std::cout << "DOWN is pressed\n";
						break;
					}

					case SDLK_LEFT:
					{
						m_publisher.Notify(leftArrow, true);
						std::cout << "LEFT is pressed\n";
						break;
					}

					case SDLK_RIGHT:
					{
						m_publisher.Notify(rightArrow, true);
						std::cout << "RIGHT is pressed\n";
						break;
					}

					case SDLK_SPACE:
					{
						m_publisher.Notify(spacebarKey, true);
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
					case SDLK_UP:
					{
						m_publisher.Notify(upArrow, false);
						std::cout << "UP is released\n";
						break;
					}

					case SDLK_DOWN:
					{
						m_publisher.Notify(downArrow, false);
						std::cout << "DOWN is released\n";
						break;
					}

					case SDLK_LEFT:
					{
						m_publisher.Notify(leftArrow, false);
						std::cout << "LEFT is released\n";
						break;
					}

					case SDLK_RIGHT:
					{
						m_publisher.Notify(rightArrow, false);
						std::cout << "RIGHT is released\n";
						break;
					}

					case SDLK_SPACE:
					{
						m_publisher.Notify(spacebarKey, false);
						std::cout << "SPACE is released\n";
						break;
					}
				}
				break;
			}

			case SDL_MOUSEMOTION:
			{
				m_publisher.Notify(event.motion.x, event.motion.y);
				std::cout << "Mouse position: " << event.motion.x << ", " << event.motion.y << "\n";
				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						m_publisher.Notify(leftMouseKey, true);
						std::cout << "LEFT mousebutton pressed\n";
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						m_publisher.Notify(rightMouseKey, false);
						std::cout << "RIGHT mousebutton pressed\n";
						break;
					}
				}
				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						m_publisher.Notify(leftMouseKey, false);
						std::cout << "LEFT mousebutton released\n";
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						m_publisher.Notify(rightMouseKey, false);
						std::cout << "RIGHT mousebutton released\n";
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
