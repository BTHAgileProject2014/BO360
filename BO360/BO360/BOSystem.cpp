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
	
	//windowWidth = 800;
	//windowHeight = 600;
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

	m_deltaTime = 0;
	m_totalTime = 0;
	m_FPS = 0;
	m_timePassedMS = 0;

	return true;
}

bool BOSystem::Run()
{
	bool result = true;

	// Tick the timer.
	m_timer.Tick();

	m_totalTime = m_timer.GetTotalTimeS();
	m_deltaTime = m_timer.GetDeltaTime();
	m_FPS = m_timer.FPS();

	// Output the total time and delta time to the window title for debugging.
	#ifdef DEBUG	
		m_string = "Total time: " + std::to_string(m_totalTime) + " seconds. Delta time: " + std::to_string(m_deltaTime) + " milliseconds. FPS: " + std::to_string(m_FPS);
		BOGraphicInterface::SetWindowTitle(m_string);
	#endif

	m_timePassedMS += m_deltaTime;

	if (m_timePassedMS > 2)
	{
		// ========== UPDATE =========

		// Update the input manager.
		result = m_input.Update();

		// Update all of the objects
		m_objectManager.Update();

		// ============================


		// ========== RENDER ==========
		BOGraphicInterface::Clear();

		// Render all of the objects.
		m_objectManager.Draw();

		BOGraphicInterface::Present();
		// ============================

		m_timePassedMS = 0;
	}
	
	return result;
}

void BOSystem::Shutdown()
{
	m_input.Shutdown();
}