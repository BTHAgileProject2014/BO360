#include "BOInput.h"
#include <iostream>

// To keep track of key indexes in a reasonable way
enum BOInputKey
{
	BOInput_Up,
	BOInput_Down,
	BOInput_Left,
	BOInput_Right,
	BOInput_Space,
    BOInput_Enter,
	BOInput_M1,
	BOInput_M2,
	BOInput_z,
	BOInput_x,
    BOInput_f,
    BOInput_t
};

BOInput::BOInput()
{

}

BOInput::~BOInput()
{

}

bool BOInput::Initialize()
{
	for (int i = 0; i < 11; i++)
	{
		m_buttonsPressed[i] = false;
	}
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
						if (!m_buttonsPressed[BOInput_Up])
						{
							m_buttonsPressed[BOInput_Up] = true;
							m_publisher.Notify(upArrow, true);
#ifdef DEBUG
							std::cout << "UP is pressed\n";
#endif
						}
						break;
					}

					case SDLK_DOWN:
					{
						if (!m_buttonsPressed[BOInput_Down])
						{
							m_buttonsPressed[BOInput_Down] = true;
							m_publisher.Notify(downArrow, true);
#ifdef DEBUG
							std::cout << "DOWN is pressed\n";
#endif
						}
						break;
					}

					case SDLK_LEFT:
					{
						if (!m_buttonsPressed[BOInput_Left])
						{
							m_buttonsPressed[BOInput_Left] = true;
							m_publisher.Notify(leftArrow, true);
#ifdef DEBUG
							std::cout << "LEFT is pressed\n";
#endif	
						}
						break;
					}

					case SDLK_RIGHT:
					{
						if (!m_buttonsPressed[BOInput_Right])
						{
							m_buttonsPressed[BOInput_Right] = true;
							m_publisher.Notify(rightArrow, true);
#ifdef DEBUG
							std::cout << "RIGHT is pressed\n";
#endif
						}
						break;
					}

					case SDLK_SPACE:
					{
						if (!m_buttonsPressed[BOInput_Space])
						{
							m_buttonsPressed[BOInput_Space] = true;
							m_publisher.Notify(spacebarKey, true);
#ifdef DEBUG
							std::cout << "SPACE is pressed\n";
#endif
						}
						break;
					}

					case SDLK_ESCAPE:
					{
						// Quit using the Escape key
						m_publisher.Notify(escKey, true);
#ifdef DEBUG
						std::cout << "esc is pressed\n";
#endif
						break;
					}
                    case SDLK_RETURN:
                    {
                        if (!m_buttonsPressed[BOInput_Enter])
                        {
                            m_buttonsPressed[BOInput_Enter] = true;
                            m_publisher.Notify(enterKey, true);
                        }
#ifdef DEBUG
                        std::cout << "enter is pressed\n";
#endif
                        break;
                    }
					case SDLK_z:
					{
						if (!m_buttonsPressed[BOInput_z])
						{
							m_buttonsPressed[BOInput_z] = true;
							m_publisher.Notify(zKey, true);
#ifdef DEBUG
							std::cout << "z is pressed\n";
#endif
						}
						break;
					}
					case SDLK_x:
					{
						if (!m_buttonsPressed[BOInput_x])
						{
							m_buttonsPressed[BOInput_x] = true;
							m_publisher.Notify(xKey, true);
#ifdef DEBUG
							std::cout << "x is pressed\n";
#endif
						}
						
						break;
					}
                    case SDLK_f:
                    {
                        if (!m_buttonsPressed[BOInput_f])
                        {
                            m_buttonsPressed[BOInput_f] = true;
                            m_publisher.Notify(fKey, true);
#ifdef DEBUG
                            std::cout << "f is pressed\n";
#endif
                        }
                        break;
                    }
                    case SDLK_t:
                    {
                        if (!m_buttonsPressed[BOInput_t])
                        {
                            m_buttonsPressed[BOInput_t] = true;
                            m_publisher.Notify(tKey, true);
#ifdef DEBUG
                            std::cout << "t is pressed\n";
#endif
                        }
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
						m_buttonsPressed[BOInput_Up] = false;
						m_publisher.Notify(upArrow, false);
#ifdef DEBUG
						std::cout << "UP is released\n";
#endif
						break;
					}

					case SDLK_DOWN:
					{
						m_buttonsPressed[BOInput_Down] = false;
						m_publisher.Notify(downArrow, false);
#ifdef DEBUG
						std::cout << "DOWN is released\n";
#endif
						break;
					}

					case SDLK_LEFT:
					{
						m_buttonsPressed[BOInput_Left] = false;
						m_publisher.Notify(leftArrow, false);
#ifdef DEBUG
						std::cout << "LEFT is released\n";
#endif
						break;
					}

					case SDLK_RIGHT:
					{
						m_buttonsPressed[BOInput_Right] = false;
						m_publisher.Notify(rightArrow, false);
#ifdef DEBUG
						std::cout << "RIGHT is released\n";
#endif
						break;
					}

					case SDLK_SPACE:
					{
						m_buttonsPressed[BOInput_Space] = false;
						m_publisher.Notify(spacebarKey, false);
#ifdef DEBUG
						std::cout << "SPACE is released\n";
#endif
						break;
					}
					case SDLK_ESCAPE:
					{
						// Quit using the Escape key
						m_publisher.Notify(escKey, false);
#ifdef DEBUG
						std::cout << "esc is released\n";
#endif
						break;
					}
                    case SDLK_RETURN:
                    {
                        m_buttonsPressed[BOInput_Enter] = false;
                        m_publisher.Notify(enterKey, false);
#ifdef DEBUG
                        std::cout << "enter is released\n";
#endif
                        break;
                    }
					case SDLK_z:
					{
						m_buttonsPressed[BOInput_z] = false;
						m_publisher.Notify(zKey, false);
#ifdef DEBUG
						std::cout << "z is released\n";
#endif
						break;
					}
					case SDLK_x:
					{
						m_buttonsPressed[BOInput_x] = false;
						m_publisher.Notify(xKey, false);
#ifdef DEBUG
						std::cout << "x is released\n";
#endif
						break;
					}
                    case SDLK_f:
                    {
                        m_buttonsPressed[BOInput_f] = false;
                        m_publisher.Notify(fKey, false);
#ifdef DEBUG
                        std::cout << "f is released\n";
#endif
                        break;
                    }

                    case SDLK_t:
                    {
                        m_buttonsPressed[BOInput_t] = false;
                        m_publisher.Notify(tKey, false);
#ifdef DEBUG
                        std::cout << "t is released\n";
#endif
                        break;
                    }
				}
				break;
			}

			case SDL_MOUSEMOTION:
			{
				int2 position;
				position.x = event.motion.x;
				position.y = event.motion.y;
				m_publisher.Notify(position);
#ifdef DEBUG
				std::cout << "Mouse position: " << event.motion.x << ", " << event.motion.y << "\n";
#endif				
				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						if (!m_buttonsPressed[BOInput_M1])
						{
							m_buttonsPressed[BOInput_M1] = true;
							m_publisher.Notify(leftMouseKey, true);
#ifdef DEBUG
							std::cout << "LEFT mousebutton pressed\n";
#endif
						}
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						if (!m_buttonsPressed[BOInput_M2])
						{
							m_buttonsPressed[BOInput_M2] = true;
							m_publisher.Notify(rightMouseKey, false);
#ifdef DEBUG
							std::cout << "RIGHT mousebutton pressed\n";
#endif
						}
						break;
					}
					default:
					{
						m_buttonsPressed[BOInput_M1] = false;
						m_publisher.Notify(leftMouseKey, false);
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
						m_buttonsPressed[BOInput_M1] = false;
						m_publisher.Notify(leftMouseKey, false);
#ifdef DEBUG
						std::cout << "LEFT mousebutton released\n";
#endif
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						m_buttonsPressed[BOInput_M2] = false;
						m_publisher.Notify(rightMouseKey, false);
#ifdef DEBUG
						std::cout << "RIGHT mousebutton released\n";
#endif
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