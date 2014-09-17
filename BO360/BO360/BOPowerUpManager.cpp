#include "BOPowerUpManager.h"


BOPowerUpManager::BOPowerUpManager()
{
}


BOPowerUpManager::~BOPowerUpManager()
{
}

bool BOPowerUpManager::Initialize()
{
	m_powerUps = std::vector<BOPowerUp>();

	return true;
}

void BOPowerUpManager::Shutdown()
{
}

void BOPowerUpManager::Update(Uint32 p_deltaTime)
{
	for (unsigned int i = 0; i < m_powerUps.size(); i++)
	{
		m_powerUps[i].Update(p_deltaTime);
	}
}

void BOPowerUpManager::Draw()
{
	for (unsigned int i = 0; i < m_powerUps.size(); i++)
	{
		m_powerUps[i].Draw();
	}
}