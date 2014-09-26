#ifndef BOOBJECTMANGAGER_H_
#define BOOBJECTMANGAGER_H_

#define MAXPARTICLES 5000
#define PARTICLEPOSITIONOFFSET 17
#define PARTICLEROTATIONVARIATION 361
#define PARTICLESEXPLOSIONSPEED int2(200, 50) // MAX, MIN
#define PARTICLESPEREXPLOSION int2(50, 25) // MAX, MIN

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
#include "BOPUPadSize.h"
#include "BOShield.h"
#include "BOShieldPU.h"
#include "BOParticleSystem.h"
#include "BOHUDManager.h"
#include "BOScore.h"
#include <vector>
#include "BOBlockIron.h"
#include "BOBlockMultiTexture.h"

class BOObjectManager : public BOComponent, public BOPUSubscriber ,public BOSubscriber
{
public:
	BOObjectManager();
	~BOObjectManager();

	bool Initialize(int windowWidth, int windowHeight);
	void Shutdown();
	void Update(double p_deltaTime);
	void Draw();
	void Handle(PowerUpTypes p_type, bool p_activated);
	void Handle(InputMessages p_inputMessage);
	bool AddNewBall();
	bool LostGame();

private:
	void CheckBallOutOfBounds(int p_index);
	float2 ChangeBallPosAtStart();

	bool m_hasColided;
	int m_life;

	bool m_releaseBall;

	BOMapLoader m_mapLoader;
	std::vector<Block> m_loadedBlocks;

	BOBackground m_background;
	BOBlackHole m_blackHole;
	std::vector<BOBall*> m_ballList;
	BOPaddle m_paddle;
	BOShield m_Shield;
	int2 m_windowsSize;
  
	int2 m_ballSize;
	float2 m_ballStartPosition;
	float m_ballSpeed;
	float2 m_ballDirection;
	
  
	std::vector<BOBlock*> m_blockList;

	double m_SecondsPerParticle;
	BOParticleSystem m_particleSystem;
	const double m_PI = 3.14159265359;
	const double m_PIDiv180 = m_PI / 180;
};
#endif