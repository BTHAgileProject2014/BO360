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