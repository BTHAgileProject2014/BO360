#ifndef BOOBJECTMANGAGER_H_
#define BOOBJECTMANGAGER_H_

#include "BOComponent.h"
#include "BOBackground.h"
#include "BOObject.h"
#include "BOBlackHole.h"
#include "BOBall.h"
#include "BOPaddle.h"
#include "BOBlock.h"
#include "BOPhysics.h"
#include "BOMapLoader.h"
#include "BOPUSubscriber.h"
#include "BOPowerUpManager.h"
#include "BOSoundManager.h"
#include "BOPowerUp.h"
#include "BOMultiballs.h"
#include <vector>

class BOObjectManager : public BOComponent, public BOPUSubscriber
{
public:
	BOObjectManager();
	~BOObjectManager();

	bool Initialize(int windowWidth, int windowHeight);
	void Shutdown();
	void Update(Uint32 p_deltaTime);
	void Draw();
	void Handle(PowerUpTypes p_type, bool p_activated);

private:
	void BallDirectionChange(int p_bounceCorner);
	bool m_GravityIsOn;
	bool m_hasColided;

	BOMapLoader m_mapLoader;
	std::vector<float2> m_blockPositions;

	BOBackground m_background;
	BOBlackHole m_blackHole;
	std::vector<BOBall> m_ballList;
	BOPaddle m_paddle;
	std::vector<BOBlock> m_blockList;
	//std::vector<BOParticle> m_particleList;
	//std::vector<BOPowerUp> m_powerUPlist;
};
#endif