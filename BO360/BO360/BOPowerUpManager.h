#ifndef BOPOWERUPMANAGER_H_
#define BOPOWERUPMANAGER_H_

#include "BOPowerUp.h"
#include "BOComponent.h"
#include <vector>

class BOPowerUpManager
{
public:
	BOPowerUpManager();
	~BOPowerUpManager();
private:
	std::vector<BOPowerUp> m_PowerUps;
};

#endif