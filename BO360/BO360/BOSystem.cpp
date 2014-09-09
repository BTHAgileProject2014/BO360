#include "BOSystem.h"

BOSystem::BOSystem()
{

}

BOSystem::~BOSystem()
{

}

bool BOSystem::Initialize()
{
	return m_window.Initialize("Are we going to support multiple resolutions?", 1024, 720);
}

bool BOSystem::Run()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			return false;
		}
	}

	return true;
}

void BOSystem::Shutdown()
{

}