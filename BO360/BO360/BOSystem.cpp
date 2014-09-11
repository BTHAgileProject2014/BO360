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

	return true;

}

bool BOSystem::Run()
{
	bool result = true;
	result = m_input.Update();
	m_objectManager.Update();

	BOGraphicInterface::Clear();

	m_objectManager.Draw();

	BOGraphicInterface::Present();

	return result;
}

void BOSystem::Shutdown()
{
	m_input.Shutdown();
}