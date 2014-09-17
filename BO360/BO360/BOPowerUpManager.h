#ifndef BOPOWERUPMANAGER_H_
#define BOPOWERUPMANAGER_H_

#include "BOPowerUp.h"
#include "BOComponent.h"
#include <vector>

class BOPowerUpManager : BOComponent
{
public:
	BOPowerUpManager();
	~BOPowerUpManager();

	bool Initialize();
	void Shutdown();
private:
	std::vector<BOPowerUp> m_powerUps;
};

#endif