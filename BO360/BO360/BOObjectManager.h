#ifndef BOOBJECTMANGAGER_H_
#define BOOBJECTMANGAGER_H_

#include <vector>
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
#include "BOShield.h"
#include "BOParticleSystem.h"
#include "BOHUDManager.h"
#include "BOScore.h"
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

	bool m_hasColided; //
	int m_life; //

	bool m_releaseBall; //

	BOMapLoader m_mapLoader; //
	std::vector<Block> m_loadedBlocks; // ??

	BOBackground m_background; //
	BOBlackHole m_blackHole; //
	std::vector<BOBall*> m_ballList;
	BOPaddle m_paddle; //
	BOShield m_Shield;
	int2 m_windowsSize; //
  
	int2 m_ballSize; // Should be located in ball
	float m_ballSpeed; // Should be located in ball
  
	float2 m_ballStartPosition;
	float2 m_ballDirection;
	
  
	std::vector<BOBlock*> m_blockList;

	double m_SecondsPerParticle; // Should be moved into objects that use it
	BOParticleSystem m_particleSystem; //
	const double m_PI = 3.14159265359;
	const double m_PIDiv180 = m_PI / 180;
};
#endif