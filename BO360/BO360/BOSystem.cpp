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
}

bool BOSystem::Run()
{
	return m_input.Update();
}

void BOSystem::Shutdown()
{
	m_input.Shutdown();
}