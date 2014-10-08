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

	m_currentLevel = 0;

	return result;
}

void BOLevelManager::Shutdown()
{

}

void BOLevelManager::SetLevel(int p_indexLevel)
{
	m_currentLevel = p_indexLevel;
}

int BOLevelManager::GetNextLevel()
{
	if (texNR - nrOfLevels > m_currentLevel + 2)
	{
		m_currentLevel += 1;
	}
	return m_currentLevel;
}

int BOLevelManager::GetCurrentLevel()
{
	return m_currentLevel;
}
