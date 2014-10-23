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
	for (int i = 0; i < LAST_OF_BOINPUT; i++)
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
					case SDLK_g:
					{
						if (!m_buttonsPressed[BOInput_g])
						{
							m_buttonsPressed[BOInput_g] = true;
							m_publisher.Notify(gKey, true);
#ifdef DEBUG
							std::cout << "g is pressed\n";
#endif
						}
						break;
					}
					case SDLK_h:
					{
						if (!m_buttonsPressed[BOInput_h])
						{
							m_buttonsPressed[BOInput_h] = true;
							m_publisher.Notify(hKey, true);
#ifdef DEBUG
							std::cout << "g is pressed\n";
#endif
						}
						break;
					}
					case SDLK_j:
					{
						if (!m_buttonsPressed[BOInput_j])
						{
							m_buttonsPressed[BOInput_j] = true;
							m_publisher.Notify(jKey, true);
#ifdef DEBUG
							std::cout << "g is pressed\n";
#endif
						}
						break;
					}
					case SDLK_m:
					{
						if (!m_buttonsPressed[BOInput_m])
						{
							m_buttonsPressed[BOInput_m] = true;
							m_publisher.Notify(mKey, true);
#ifdef DEBUG
							std::cout << "m is pressed\n";
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
					case SDLK_g:
					{
						m_buttonsPressed[BOInput_g] = false;
						m_publisher.Notify(gKey, false);
#ifdef DEBUG
						std::cout << "g is released\n";
#endif
						break;
					}
					case SDLK_h:
					{
						m_buttonsPressed[BOInput_h] = false;
						m_publisher.Notify(hKey, false);
#ifdef DEBUG
						std::cout << "g is released\n";
#endif
						break;
					}
					case SDLK_j:
					{
						m_buttonsPressed[BOInput_j] = false;
						m_publisher.Notify(jKey, false);
#ifdef DEBUG
						std::cout << "g is released\n";
#endif
						break;
					}
					case SDLK_m:
					{
						m_buttonsPressed[BOInput_m] = false;
						m_publisher.Notify(mKey, false);
#ifdef DEBUG
						std::cout << "m is released\n";
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