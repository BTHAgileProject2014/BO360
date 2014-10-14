#ifndef BOSHIELD_H_
#define BOSHIELD_H_

#include "BOPowerUp.h"
#include "BOPhysics.h"
#include "BOPowerUpManager.h"
#include "BOBall.h"

class BOShield
{
public:
	BOShield();
	~BOShield();

	bool Initialize(int2 p_ShieldSize, SDL_Texture* p_sprite, int2 p_WindowSize);
	bool InitializePU(float2 p_POPos, int2 p_POSize, std::string p_POFN, float p_POSpeed);
    void Update(double p_deltaTime, BOBall& p_ball);
	void Draw();
	void Shutdown();

	void SetActive(bool p_IsActive);
	void SwitchActive();
	bool GetActive();

private:
	void ChangeBallDirection(int p_BounceCorner);

	SDL_Texture* m_ShieldSprite;
	int2 m_ShieldSize;
	sphere m_ShieldSphere;
	int2 m_WindowSize;
	bool m_IsActive;
	int m_lifes;
};
#endif