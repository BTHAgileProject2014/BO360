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

	void Update(Uint32 p_deltaTime);
	void Draw();
private:
	std::vector<BOPowerUp> m_powerUps;
};

#endif