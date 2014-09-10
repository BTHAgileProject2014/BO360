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
	m_input.Initialize();
	
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
	m_objectManager.Update();

	BOGraphicInterface::Clear();

	m_objectManager.Draw();

	return m_input.Update();
	BOGraphicInterface::Present();

	return true;
}

void BOSystem::Shutdown()
{
	m_input.Shutdown();
}