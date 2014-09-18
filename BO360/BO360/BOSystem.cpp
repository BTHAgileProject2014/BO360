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

	result = m_timer.Initialize();
	if (!result)
	{
		return false;
	}

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

	result = m_powerUpManager.Initialize(windowWidth, windowHeight);
	if (!result)
	{
		return false;
	}

	result = m_powerUpManager.Initialize(windowWidth, windowHeight);
	if (!result)
	{
		return false;
	}

	m_deltaTime = 0;
	m_totalTime = 0;
	m_FPS = 0;

	result = BOTextManager::Initialize();
	if (!result)
	{
		return false;
	}

	return true;
}

bool BOSystem::Run()
{
	bool result = true;

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

		// Update all of the objects
		m_objectManager.Update(m_deltaTime);

		// Update the power-ups
		m_powerUpManager.Update(m_deltaTime);

		// Update Sound 
		BOSoundManager::Update(); // Empty so far.
		if (m_objectManager.GetPop())
		{
			BOSoundManager::PlayPopSound();
		}

		// ============================

		// ========== RENDER ==========
		BOGraphicInterface::Clear();

		// Render all of the objects.
		m_objectManager.Draw();

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