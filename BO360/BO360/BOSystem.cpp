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
	return m_input.Update();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			return false;
		}
	}

	m_objectManager.Update();
	m_objectManager.Draw();

	return true;
}

void BOSystem::Shutdown()
{
	m_input.Shutdown();
}