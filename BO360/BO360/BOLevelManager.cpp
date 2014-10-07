#include "BOLevelManager.h"


BOLevelManager::BOLevelManager()
{
}


BOLevelManager::~BOLevelManager()
{
}

bool BOLevelManager::Initialize()
{
	bool result = true;

	m_levelList = std::vector <int>();


	return result;
}

void BOLevelManager::Shutdown()
{

}


/*
tryck knapp
välj level
ladda level
starta level
*/