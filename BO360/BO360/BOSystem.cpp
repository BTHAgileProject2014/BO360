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
	if (!BOTextureManager::Initialize("Neon"))
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
	BOGlobals::GAME_STATE = MENU;
	if (!m_stateManager.Initialize(int2(m_windowWidth, m_windowHeight)))
	{
		std::cout << "Initialize state manager failed!" << std::endl;

		return false;
	}
	m_stateManager.SetButtonActionLevel(0, LEVEL);

    // Initialize the cutscene manager.
    m_cutsceneManager.Initialize(int2(1300, 900));
    m_cutsceneManager.LoadCutscene(0);

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

    // Load the cutscenes.
    m_cutsceneManager.LoadCutscene(p_levelIndex);

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
        bool updateMap = (BOGlobals::GAME_STATE == RUNNING || BOGlobals::GAME_STATE == VICTORY || BOGlobals::GAME_STATE == DEFEAT);
        bool updateRest = (BOGlobals::GAME_STATE != RUNNING);
        bool renderMap = (BOGlobals::GAME_STATE == RUNNING || BOGlobals::GAME_STATE == VICTORY || BOGlobals::GAME_STATE == DEFEAT || BOGlobals::GAME_STATE == PAUSED);
        bool renderRest = (BOGlobals::GAME_STATE != RUNNING);

		if (updateMap)
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
				// Go to victory screen
				BOGlobals::GAME_STATE = VICTORY;

				// Unlock new map
				m_stateManager.SetButtonActionLevel(m_levelManager.GetCurrentLevel() + 1, LEVEL);
			}
			// Check if the player lost the current game
			else if (m_objectManager.LostGame())
			{
				// Go to defeat screen
				BOGlobals::GAME_STATE = DEFEAT;
			}
		}

		if (updateRest)
		{
            // Update TechTree
            if (BOGlobals::GAME_STATE == TECHTREE)
            {
                m_techTreeManager.Update();
            }

            // Update TechTree
            if (BOGlobals::GAME_STATE == CUTSCENE)
            {
                HandleAction(m_cutsceneManager.Update());
            }

			// Update approperiate menu and handle the actions.
			HandleAction(m_stateManager.Update(BOGlobals::GAME_STATE));
            
			if (m_quit)
			{
				result = false;
			}
		}

		// ============================

		// ========== RENDER ==========
		BOGraphicInterface::Clear();

		if (renderMap)
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

		if (renderRest)
		{
			// Draw approperiate menu.
			m_stateManager.Draw(BOGlobals::GAME_STATE);

            // Draw TechTree
            if (BOGlobals::GAME_STATE == TECHTREE)
            {
                m_techTreeManager.Draw();
            }

            // Draw cutscenes
            if (BOGlobals::GAME_STATE == CUTSCENE)
            {
                m_cutsceneManager.Draw();
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
    ShutdownMap();
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
    m_cutsceneManager.Shutdown();
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
				BOGlobals::GAME_STATE = MENU;
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
                m_techTreeManager.SetTechPoint(0, false);
				BOGlobals::GAME_STATE = RUNNING;
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
				BOGlobals::GAME_STATE = RUNNING;

				break;
			}

			// NEXT, load next map.
			case(NEXT) :
			{
                ShutdownMap();
                BOGlobals::GAME_STATE = TECHTREE;
				int currentLevel = m_levelManager.GetCurrentLevel();
				int nextLevel = m_levelManager.GetNextLevel();
				if (currentLevel == nextLevel)	// Same if last map
				{
					BOGlobals::GAME_STATE = MENU;
					m_levelManager.SetLevel(0);
				}
                //m_techTreeManager.Reset();
                m_techTreeManager.SetTechPoint(m_levelManager.GetCurrentLevel(), false);
                break;
            }

			// RETRY, reload the map.
			case(RETRY) :
			{
                ShutdownMap();
				BOGlobals::GAME_STATE = RUNNING;
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
				BOGlobals::GAME_STATE = LEVELSELECTOR;
				break;
			}

			case (LEVEL) :
			{
				int index =	m_stateManager.GetLevelIndex();

                // Special case for the first level, skipping the tech tree
                if (index == 0)
                {
                    
                    BOGlobals::GAME_STATE = RUNNING;

                    if (!InitializeMap(0))
                    {
                        std::cout << "Press ENTER to quit." << std::endl;
                        std::cin.get();
                        m_quit = true;
                    }
                }
                else if (index != -1)
				{
					BOGlobals::GAME_STATE = TECHTREE;
					m_levelManager.SetLevel(index);
				}
                m_techTreeManager.Reset();
                m_techTreeManager.SetTechPoint(index, true);
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
                BOGlobals::GAME_STATE = RUNNING;
                break;
            }
		}
	}
}

void BOSystem::Handle(InputMessages p_inputMessages)
{
	if (BOGlobals::GAME_STATE == RUNNING && p_inputMessages.escKey)
	{
		BOGlobals::GAME_STATE = PAUSED;
	}

	if (BOGlobals::GAME_STATE == LEVELSELECTOR && p_inputMessages.escKey)
	{
		BOGlobals::GAME_STATE = MENU;
	}

    if (BOGlobals::GAME_STATE == RUNNING && p_inputMessages.tKey)
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