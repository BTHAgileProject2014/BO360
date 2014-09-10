#include "BOSystem.h"


BOSystem::BOSystem()
{

}

BOSystem::~BOSystem()
{

}

bool BOSystem::Initialize()
{
	m_input.Initialize();
	return m_window.Initialize("Are we going to support multiple resolutions?", 1024, 720);

	bool result;

	windowWidth = 1024;
	windowHeight = 720;

	result = m_window.Initialize("Are we going to support multiple resolutions?", windowWidth, windowHeight);
	if (!result)
	{
		return false;
	}

	result = m_objectManager.Initialize(windowWidth, windowHeight);
	if (!result)
	{
		return false;
	}

	return true;

}

bool BOSystem::Run()
{
	m_objectManager.Update();
	m_objectManager.Draw();

	return m_input.Update();
}

void BOSystem::Shutdown()
{
	m_input.Shutdown();
}