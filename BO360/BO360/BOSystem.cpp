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

	// Intilialize timer.
	m_deltaTime = 0;
	m_totalTime = 0;
	m_FPS = 0;

	result = m_timer.Initialize();
	if (!result)
	{
		std::cout << "Initialize timer failed!" << std::endl;

		return false;
	}

	// Initlialize input manager.
	result = m_input.Initialize();
	if (!result)
	{
		std::cout << "Initialize input manager failed!" << std::endl;

		return false;
	}
	

	// Set screen size.
	m_windowWidth = 1300;
	m_windowHeight = 900;

	// Initlialize the graphichs engine.
	if (!BOGraphicInterface::Initialize(m_windowWidth, m_windowHeight))
	{
		std::cout << "Initialize graphics engine failed!" << std::endl;

		return false;
	}

	// Initlialize the text manager.
	result = BOTextManager::Initialize();
	if (!result)
	{
		std::cout << "Initialize text manager failed!" << std::endl;

		return false;
	}

	// Initialize the state handler.
	m_gameState = MENU;
	if (!m_stateManager.Initialize(int2(m_windowWidth, m_windowHeight)))
	{
		std::cout << "Initialize state manager failed!" << std::endl;

		return false;
	}

	return true;
}

bool BOSystem::InitializeMap()
{
	bool result;

	// Initilialize the object manager.
	result = m_objectManager.Initialize(m_windowWidth, m_windowHeight);
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

	// Initlialize the power up manager.
	result = m_powerUpManager.Initialize(m_windowWidth, m_windowHeight);
	if (!result)
	{
		std::cout << "Initialize power up manager failed!" << std::endl;

		return false;
	}

	result = BOHUDManager::Initialize(true);
	if (!result)
	{
		std::cout << "Initialize HUD failed!" << std::endl;

		return false;
	}

	// Example usage of HUD
	BOHUDManager::SetScore(1000000);
	BOHUDManager::SetLives(5);
	BOHUDManager::SetLevel(1);

	return true;
}

bool BOSystem::Run()
{
	bool result = true;

	// Get the initial delta time.
	m_deltaTime += m_timer.GetDeltaTime();

	if (m_deltaTime > 2)
	{
		// low-cap the fps to never do less than 10 updates / sec
		if (m_deltaTime > 100)
		{
			m_deltaTime = 100;
		}

		// ========== UPDATE =========

		// Tick the timer.
		m_timer.Tick();
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
		}

		else
		{
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
		}

		BOGraphicInterface::Present();
		// ============================

		m_deltaTime = 0;
	}
	
	return result;
}

void BOSystem::Shutdown()
{
	m_input.Shutdown();
	m_objectManager.Shutdown();
	m_powerUpManager.Shutdown();
	m_stateManager.Shutdown();
	BOSoundManager::Shutdown();
	BOTextManager::Shutdown();
	BOHUDManager::Shutdown();
}

void BOSystem::HandleAction(int p_action)
{
	if (p_action != 0)
	{
		switch (p_action)
		{
			// QUIT, return to main menu.
			case(-2) :
			{
				m_gameState = MENU;

				break;
			}

			// EXIT, quit the game.
			case(-1) :
			{
				m_quit = true;

				break;
			}

			// PLAY STORY MODE.
			case(1) :
			{
				m_gameState = RUNNING;
				if (!InitializeMap())
				{
					std::cout << "Initialize map failed to complete! Press ENTER to quit." << std::endl;
					std::cin.get();

					m_quit = true;
				}

				break;
			}

			// PLAY ENDLESS MODE.
			case(2) :
			{
				break;
			}

			// PLAY HARDCORE MODE.
			case(3) :
			{
				break;

			}

			// RESUME, return to running.
			case(4) :
			{
				m_gameState = RUNNING;

				break;
			}

			// NEXT, load next map.
			case(5) :
			{
				break;
			}

			// RETRY, reload the map.
			case(6) :
			{
				break;

			}
		}
	}
}