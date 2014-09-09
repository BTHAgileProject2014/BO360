#include "BOSystem.h"

BOSystem::BOSystem()
{

}

BOSystem::~BOSystem()
{

}

bool BOSystem::Initialize()
{
	return m_window.Initialize();
}

bool BOSystem::Run()
{
	return true;
}

void BOSystem::Shutdown()
{

}