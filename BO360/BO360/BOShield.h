#ifndef BOSHIELD_H_
#define BOSHIELD_H_
#include "BOPowerUp.h"
#include "BOPhysics.h"
#include "BOPowerUpManager.h"

class BOShield
{
public:
	BOShield();
	~BOShield();

	bool Initialize(int2 p_ShieldSize, std::string p_ShieldFN, int2 p_WindowSize);
	bool InitializePU(float2 p_POPos, int2 p_POSize, std::string p_POFN, float p_POSpeed);
	float2 Update(Uint32 p_deltaTime, sphere p_Ball, float2 p_BallDirection);
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

};

#endif