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
	
	windowWidth = 800;
	windowHeight = 600;

	if (!BOGraphicInterface::Initialize())
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

	m_currentFPS = 0;
	m_averageFPS = 60;
	m_FPS = 60;

	return true;
}

bool BOSystem::Run()
{
	bool result = true;

	// ========== UPDATE =========

	// Tick the timer.
	m_timer.Tick();

	// Output the total time and delta time to the window title for debugging.
	if (DEBUG)
	{
		m_totalTime = m_timer.GetTotalTimeS();
		m_deltaTime = m_timer.GetDeltaTime();
		if (m_deltaTime > 0)
		{
			m_FPS = (int)FPScounter(m_deltaTime);
		}
		
		m_string = "Total time: " + std::to_string(m_totalTime) + " seconds. Delta time: " + std::to_string(m_deltaTime) + " milliseconds. FPS: " + std::to_string(m_FPS);
		BOGraphicInterface::SetWindowText(m_string);
	}

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

	return result;
}

float BOSystem::FPScounter(Uint32 p_deltaTime)
{
	m_currentFPS = (1.0f / p_deltaTime) * 1000.0F;

	m_averageFPS = (m_currentFPS * 0.1f) + (m_averageFPS * 0.9f);

	return m_averageFPS;
}

void BOSystem::Shutdown()
{
	m_input.Shutdown();
}