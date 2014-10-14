#include "BOSystem.h"

BOSystem::BOSystem()
{

}

BOSystem::~BOSystem()
{

}

bool BOSystem::Initialize()
{
	bool result;
	m_quit = false;

	// Initialize timer.
	m_deltaTime = 0;
	m_totalTime = 0;
	m_FPS = 0;

	result = m_timer.Initialize();
	if (!result)
	{
		std::cout << "Initialize timer failed!" << std::endl;

		return false;
	}

	result = m_techTreeEffects.Initialize();
	if (!result)
	{
		return false;
	}


	// Initialize input manager.
	result = m_input.Initialize();
	if (!result)
	{
		std::cout << "Initialize input manager failed!" << std::endl;

		return false;
	}

	// Set screen size.
	m_windowWidth = 1300;
	m_windowHeight = 900;

	// Initialize the graphics engine.
	if (!BOGraphicInterface::Initialize(m_windowWidth, m_windowHeight))
	{
		std::cout << "Initialize graphics engine failed!" << std::endl;

		return false;
	}

	// Initialize the texturemanager
	if (!BOTextureManager::Initialize("Industrial"))
	{
		std::cout << "Initialize texturemanager failed!" << std::endl;

		return false;
	}

	// Initialize the text manager.
	result = BOTextManager::Initialize();
	if (!result)
	{
		std::cout << "Initialize text manager failed!" << std::endl;

		return false;
	}

	result = m_levelManager.Initialize();
	if (!result)
	{
		std::cout << "Initialize level manager failed!" << std::endl;

		return false;
	}

	// Initialize the state handler.
	m_gameState = MENU;
	if (!m_stateManager.Initialize(int2(m_windowWidth, m_windowHeight)))
	{
		std::cout << "Initialize state manager failed!" << std::endl;

		return false;
	}
	m_stateManager.SetButtonActionLevel(0, LEVEL);

	// Add system as an subscriber
	BOPublisher::AddSubscriber(this);

    if (!m_techTreeManager.Initialize(BOGraphicInterface::GetWindowSize()))
    {
        return false;
    }

	return true;
}

bool BOSystem::InitializeMap()
{
	bool result;

	// Initialize the power up manager.
	result = m_powerUpManager.Initialize();
	if (!result)
	{
		std::cout << "Initialize power up manager failed!" << std::endl;

		return false;
	}

	result = BOHUDManager::Initialize();
	if (!result)
	{
		std::cout << "Initialize HUD failed!" << std::endl;

		return false;
	}

	// Initilialize the object manager.
	result = m_objectManager.Initialize(m_windowWidth, m_windowHeight, -1);
	if (!result)
	{
		std::cout << "Initialize object manager failed!" << std::endl;

		return false;
	}

	// Initialize the sound engine.
	if(!BOSoundManager::Initialize())
	{
		std::cout << "Initialize sound manager failed!" << std::endl;

		return false;
	}

	// Initialize score
	if (!BOScore::Initialize())
	{
		std::cout << "Failed to initialize score in system";
		return false;
	}

	// Set level on HUD
	BOHUDManager::SetLevel(1);

    // Set the time scale to 1.0
    BOPhysics::SetTimeScale(1.0f);

	return true;
}

bool BOSystem::InitializeMap(int p_levelIndex)
{
	bool result;

	// Initialize the power up manager.
	result = m_powerUpManager.Initialize();
	if (!result)
	{
		std::cout << "Initialize power up manager failed!" << std::endl;

		return false;
	}

	result = BOHUDManager::Initialize();
	if (!result)
	{
		std::cout << "Initialize HUD failed!" << std::endl;

		return false;
	}

	// Initilialize the object manager.
	result = m_objectManager.Initialize(m_windowWidth, m_windowHeight, p_levelIndex);
	if (!result)
	{
		std::cout << "Initialize object manager failed!" << std::endl;

		return false;
	}

	// Initialize the sound engine.
	if (!BOSoundManager::Initialize())
	{
		std::cout << "Initialize sound manager failed!" << std::endl;

		return false;
	}

	// Initialize score
	if (!BOScore::Initialize())
	{
		std::cout << "Failed to initialize score in system";
		return false;
	}

	// Set the correct level on the HUD
	BOHUDManager::SetLevel(p_levelIndex + 1);

	// Set the time scale to 1.0
	BOPhysics::SetTimeScale(1.0f);

	return true;
}

bool BOSystem::Run()
{
	bool result = true;
	m_timer.Tick();
	// Get the initial delta time.
	m_deltaTime += m_timer.GetDeltaTime();

	if (m_deltaTime > 0.0)
	{
		// Low-cap the fps to never do less than 10 updates / sec
		if (m_deltaTime > 0.1)
		{
            std::cout << "DT Overflow" << std::endl;
			m_deltaTime = 0.1;
		}

		// ========== UPDATE =========

		// Tick the timer.
		m_totalTime = m_timer.GetTotalTimeS();
		m_FPS = m_timer.FPS();

		// Output the total time and delta time to the window title for debugging.
#ifdef DEBUG
		m_string = "Total time: " + std::to_string(m_totalTime) + " seconds. Delta time: " + std::to_string(m_deltaTime) + " milliseconds. FPS: " + std::to_string(m_FPS);
		BOGraphicInterface::SetWindowTitle(m_string);
#endif

		// Update the input manager.
		result = m_input.Update();

		if (m_gameState == RUNNING)
		{
			// Update all of the objects.
			m_objectManager.Update(m_deltaTime);

			// Update the power ups.
			m_powerUpManager.Update(m_deltaTime);

			// Update the sound Engine.
			BOSoundManager::Update(); // Empty so far.

			// Check if the player won the current game
			if (m_objectManager.WonGame())
			{
				// Shutdown map
				ShutdownMap();

				// Go to victory screen
				m_gameState = VICTORY;

				// Unlock new map
				m_stateManager.SetButtonActionLevel(m_levelManager.GetCurrentLevel() + 1, LEVEL);
			}
			// Check if the player lost the current game
			else if (m_objectManager.LostGame())
			{
				// Shutdown map
				ShutdownMap();

				// Go to defeat screen
				m_gameState = DEFEAT;
			}
		}

		else
		{
            // Update TechTree
            if (m_gameState == TECHTREE)
            {
                m_techTreeManager.Update();
            }

			// Update approperiate menu and handle the actions.
			HandleAction(m_stateManager.Update(m_gameState));

			if (m_quit)
			{
				result = false;
			}
		}

		// ============================

		// ========== RENDER ==========
		BOGraphicInterface::Clear();

		if (m_gameState == RUNNING)
		{
			// Render all of the objects.
			m_objectManager.Draw();

			// Render the power-ups
			m_powerUpManager.Draw();

			// Render text
			BOTextManager::DrawTexts();

			//RenderHUD
             BOHUDManager::Draw();

		}

		else
		{
			// Draw approperiate menu.
			m_stateManager.Draw(m_gameState);

            // Draw TechTree
            if (m_gameState == TECHTREE)
            {
                m_techTreeManager.Draw();

            }
		}
		BOGraphicInterface::Present();
		// ============================

		m_deltaTime = 0;
	}
	


	return result;
}

void BOSystem::Shutdown()
{
    m_techTreeManager.Shutdown();
	BOPublisher::Unsubscribe(this);
	m_input.Shutdown();
	m_objectManager.Shutdown();
	m_powerUpManager.Shutdown();
	m_stateManager.Shutdown();
	m_levelManager.Shutdown();
	BOSoundManager::Shutdown();
	BOTextManager::Shutdown();
	BOHUDManager::Shutdown();
	BOTextureManager::Shutdown();
}

void BOSystem::HandleAction(ButtonAction p_action)
{
	if (p_action != NOACTION)
	{
		switch (p_action)
		{
			// QUIT, return to main menu.
			case(QUIT) :
			{
				ShutdownMap();
				m_gameState = MENU;
				m_levelManager.SetLevel(0);

				break;
			}

			// EXIT, quit the game.
			case(EXIT) :
			{
				m_quit = true;

				break;
			}

			// PLAY STORY MODE.
			case(STORY) :
			{
                // Reset tech tree
                m_techTreeManager.Reset();
				m_gameState = RUNNING;
				if (!InitializeMap(0))
				{
					std::cout << "Press ENTER to quit." << std::endl;
					std::cin.get();

					m_quit = true;
				}

				break;
			}

			// VIEW HIGHSCORE
			case(HIGHSCORE) :
			{
				break;
			}

			// RESUME, return to running.
			case(RESUME) :
			{
				m_gameState = RUNNING;

				break;
			}

			// NEXT, load next map.
			case(NEXT) :
			{
                m_gameState = TECHTREE;
				int currentLevel = m_levelManager.GetCurrentLevel();
				int nextLevel = m_levelManager.GetNextLevel();
				if (currentLevel == nextLevel)	// Same if last map
				{
					m_gameState = MENU;
					m_levelManager.SetLevel(0);
				}
                break;
            }

			// RETRY, reload the map.
			case(RETRY) :
			{
				m_gameState = RUNNING;
				if (!InitializeMap(m_levelManager.GetCurrentLevel()))
				{
					std::cout << "Press ENTER to quit." << std::endl;
					std::cin.get();

					m_quit = true;
				}
				break;

			}
			case (LEVELSELECT) :
			{
				// Kolla index och ladda bana.
				m_gameState = LEVELSELECTOR;
				break;
			}
			case (LEVEL) :
			{
				int index =	m_stateManager.GetLevelIndex();

                // Special case for the first level, skipping the tech tree
                if (index == 0)
                {
                    m_techTreeManager.Reset();
                    m_gameState = RUNNING;

                    if (!InitializeMap(0))
                    {
                        std::cout << "Press ENTER to quit." << std::endl;
                        std::cin.get();

                        m_quit = true;
                    }
                }
                else if (index != -1)
				{
					m_gameState = TECHTREE;
					m_levelManager.SetLevel(index);
					
				}
				break;
			}
            case(TECHTREEACTION) :
            {
                // Initialize the new map
                if (!InitializeMap(m_levelManager.GetCurrentLevel()))
                {
                    std::cout << "Press ENTER to quit." << std::endl;
                    std::cin.get();

                    m_quit = true;
                }
                m_gameState = RUNNING;
                break;
            }
		}
	}
}

void BOSystem::Handle(InputMessages p_inputMessages)
{
	if (m_gameState == RUNNING && p_inputMessages.escKey)
	{
		m_gameState = PAUSED;
	}

	if (m_gameState == LEVELSELECTOR && p_inputMessages.escKey)
	{
		m_gameState = MENU;
	}

    if (m_gameState == RUNNING && p_inputMessages.tKey)
    {

    }

    if (p_inputMessages.xKey)
    {
        for (int i = 0; i < 100; i++)
        {
            m_stateManager.SetButtonActionLevel(i, LEVEL);
        }
        
    }
}

void BOSystem::ShutdownMap()
{
	m_objectManager.Shutdown();
	m_powerUpManager.Shutdown();
	BOHUDManager::Shutdown();
	BOScore::Shutdown();
}