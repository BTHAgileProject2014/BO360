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

	result = m_input.Initialize();
	if (!result)
	{
		return false;
	}
	
	windowWidth = 1300;
	windowHeight = 900;

	if (!BOGraphicInterface::Initialize(windowWidth, windowHeight))
	{
		return false;
	}

	result = m_powerUpManager.Initialize(windowWidth, windowHeight);
	if (!result)
	{
		return false;
	}

	result = m_objectManager.Initialize(windowWidth, windowHeight);
	if (!result)
	{
		return false;
	}

	if(!BOSoundManager::Initialize())
	if (!result)
	{
		return false;
	}

	m_deltaTime = 0;
	m_totalTime = m_timer.GetDeltaTime();
	m_FPS = 0;

	result = BOTextManager::Initialize();
	if (!result)
	{
		return false;
	}

	result = m_extraBall.Initialize(float2(10, 10), int2(80, 80), "Bilder/placeholderPowerup1.png", 1.0f, int2(windowWidth, windowHeight));
	if (!result)
	{
		return false;
	}
	m_powerUpManager.AddPowerUp(m_extraBall);
	return true;
}

bool BOSystem::Run()
{
	bool result = true;

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

	// Update all of the objects
		m_objectManager.Update(m_deltaTime);

		// Update the power-ups
		m_powerUpManager.Update(m_deltaTime);

		// Update Sound 
		BOSoundManager::Update(); // Empty so far.

	// ============================

	// ========== RENDER ==========
	BOGraphicInterface::Clear();

	// Render all of the objects.
	m_objectManager.Draw();

		m_powerUpManager.Draw();

		// Render text
		BOTextManager::DrawTexts();

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
	BOSoundManager::Shutdown();
	BOTextManager::Shutdown();
}