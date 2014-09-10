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

	windowWidth = 800;
	windowHeight = 600;

	BOGraphicInterface::Initialize();

	result = m_objectManager.Initialize(windowWidth, windowHeight);
	if (!result)
	{
		return false;
	}

	return true;
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

	m_objectManager.Update();

	BOGraphicInterface::Clear();

	m_objectManager.Draw();

	BOGraphicInterface::Present();

	return true;
}

void BOSystem::Shutdown()
{

}