#ifndef BOPOWERUPMANAGER_H_
#define BOPOWERUPMANAGER_H_

#include "BOUtility.h"
#include "BOPowerUp.h"
#include "BOPUSubscriber.h"
#include "BOComponent.h"
#include <vector>

class BOPowerUpManager : BOComponent
{
public:
	BOPowerUpManager();
	~BOPowerUpManager();

	bool Initialize(int p_windowsWidth, int p_windowHeight);
	void Shutdown();

	void Update(Uint32 p_deltaTime);
	void Draw();

	static void Notify(PowerUpTypes p_type, bool p_acivated);
	static void AddSubscriber(BOPUSubscriber* p_subscriber);
	static void Unsubscribe(BOPUSubscriber* p_subscriber);
	static void AddPowerUp(BOPowerUp* p_powerUp);
	static int GetPowerUpSize();
	static BOPowerUp* GetPowerUp(int p_nr);
private:
	static std::vector<BOPUSubscriber*> m_subscribers;
	static std::vector<BOPowerUp*> m_powerUps;
	int2 m_windowSize;

	
};

#endif