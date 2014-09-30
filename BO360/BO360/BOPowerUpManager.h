#ifndef BOPOWERUPMANAGER_H_
#define BOPOWERUPMANAGER_H_

#include "BOUtility.h"
#include "BOPaddle.h"
#include "BOPowerUp.h"
#include "BOPUSubscriber.h"
#include "BOComponent.h"
#include <vector>

class BOPowerUp;
class BOPaddle;
class BOPowerUpManager : BOComponent
{
public:
	BOPowerUpManager();
	~BOPowerUpManager();

	bool Initialize();
	void Shutdown();

	void Update(double p_deltaTime);
	void Draw();

	static void Notify(PowerUpTypes p_type, bool p_acivated);
	static void AddSubscriber(BOPUSubscriber* p_subscriber);
	static void Unsubscribe(BOPUSubscriber* p_subscriber);
	static void AddPowerUp(PowerUpTypes p_type, float2 p_startPosition, BOPaddle* p_paddle, float2 p_blackholePosition);
	static void RemovePowerUp(BOPowerUp* p_powerUp);

private:
	static std::vector<BOPUSubscriber*> m_subscribers;
	static std::vector<BOPowerUp*> m_powerUps;
	
};

#endif