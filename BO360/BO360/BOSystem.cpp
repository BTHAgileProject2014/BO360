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
		return false;
	}

	// Initlialize input manager.
	result = m_input.Initialize();
	if (!result)
	{
		return false;
	}
	

	// Set screen size.
	m_windowWidth = 1300;
	m_windowHeight = 900;

	// Initlialize the graphichs engine.
	if (!BOGraphicInterface::Initialize(m_windowWidth, m_windowHeight))
	{
		return false;
	}

	// Initlialize the text manager.
	result = BOTextManager::Initialize();
	if (!result)
	{
		return false;
	}

	// Initialize the state handler.
	m_gameState = MENU;
	if (!m_stateManager.Initialize(int2(m_windowWidth, m_windowHeight)))
	{
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
		return false;
	}

	// Initilialize the sound engine.
	result = m_soundManager.Initialize();
	if (!result)
	{
		return false;
	}

	// Initlialize the power up manager.
	result = m_powerUpManager.Initialize(m_windowWidth, m_windowHeight);
	if (!result)
	{
		return false;
	}

	return result;
}

bool BOSystem::Run()
{
	bool result = true;

	// Get the initial detla time.
	m_deltaTime += m_timer.GetDeltaTime();

	if (m_deltaTime > 2)
	{
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
			// Update all of the objects
			m_objectManager.Update(m_deltaTime);

			// Update the power-ups
			m_powerUpManager.Update(m_deltaTime);

			// Update Sound 
			m_soundManager.Update(); // Empty so far.
			if (m_objectManager.GetPop())
			{
				m_soundManager.PlayPopSound();
			}
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

			// Render text
			BOTextManager::DrawTexts();
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
	m_soundManager.Shutdown();
	BOTextManager::Shutdown();
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
				InitializeMap();

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