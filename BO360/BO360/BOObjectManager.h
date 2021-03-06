#ifndef BOOBJECTMANGAGER_H_
#define BOOBJECTMANGAGER_H_

#include <vector>
#include "BOGlobals.h"
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
#include "BOShield.h"
#include "BOParticleSystem.h"
#include "BOHUDManager.h"
#include "BOScore.h"
#include "BOBlockIron.h"
#include "BOBlockMultiTexture.h"
#include "BOKeyManager.h"
#include "BOTextureManager.h"
#include "BOSlowTime.h"
#include "BOShockwave.h"
#include "BOBoss.h"
#include "BOBossInvader.h"

class BOObjectManager : public BOComponent, public BOPUSubscriber ,public BOSubscriber
{
public:
	BOObjectManager();
	~BOObjectManager();

	bool Initialize(int windowWidth, int windowHeight, int p_levelIndex);
	void Shutdown();
	void Update(double p_deltaTime);
	void Draw();

	void Handle(PowerUpTypes p_type, bool p_activated);
	void Handle(InputMessages p_inputMessage);

	bool AddNewBall();
	bool LostGame();
	bool WonGame();

private:
	bool LoadBlocksFromMap(int p_index);
	void CheckBallOutOfBounds(int p_index);
	void BallBlockCollision(BOBall* p_ball);
	void BallPadCollision(BOBall* p_ball);
	bool BallDied(BOBall* p_ball);
	void UpdateParticles(double p_deltaTime);
    void ActivateShockwave();
	void CheckBallToBall(int i);
	void BallNewlyLaunched(BOBall* ball);
    void PewPewPew();
	void ActivateMegaPad();
	void GiantBall();
	void QuantumFuelActivate();
    Textures GetTexture(PowerUpTypes p_type);

	int m_life;
    bool m_continue;
	bool m_giantBallActive;

	BOMapLoader m_mapLoader;
	BOBackground m_background;
	BOBlackHole m_blackHole;
	BOPaddle m_paddle;
	BOShield m_Shield;
	BOParticleSystem m_particleSystem;
	std::vector<BOBall*> m_ballList;
	std::vector<BOBlock*> m_blockList;
	BOKeyManager m_keyManager;
    BOSlowTime m_slowTime;
    BOShockwave m_shockwave;
    BOBoss* m_boss;

	double m_giantBallCoolDown;
	double m_quantumFuelCoolDown;

	double m_SecondsPerParticle; // Should be moved into objects that use it
};
#endif