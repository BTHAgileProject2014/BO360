#ifndef BOOBJECTMANGAGER_H_
#define BOOBJECTMANGAGER_H_

#include "BOComponent.h"
#include "BOObject.h"
#include "BOBlackHole.h"
#include "BOBall.h"
#include <vector>

class BOObjectManager :
	public BOComponent
{
public:
	BOObjectManager();
	~BOObjectManager();

	bool Initialize(int windowWidth, int windowHeight);
	void Shutdown();
	void Update();
	void Draw();

private:
	// BOBackground;
	// BOPad m_pad;
	BOBlackHole m_blackHole;
	std::vector<BOBall> m_ballList;
	//std::vector<BOBlock> m_blockList;
	//std::vector<BOParticle> m_particleList;
	//std::vector<BOPowerUp> m_powerUPlist;
};
#endif