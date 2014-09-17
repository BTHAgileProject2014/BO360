#ifndef BOSHIELD_H_
#define BOSHIELD_H_
#include "BOPowerUp.h"
#include "BOPhysics.h"

class BOShield : BOPowerUp
{
public:
	BOShield();
	~BOShield();

	bool Initialize(float2 p_ShieldPos, int2 p_ShieldSize, std::string p_ShieldFN,
				float2 p_POPos, int2 p_POSize, std::string p_POFN);
	void Update();
	void Draw();

	void SetActive(bool p_IsActive);
	void SwitchActive();
	bool GetActive();

	


private:
	bool m_IsActive;
	SDL_Texture* m_ShieldSprite;
	int2 m_ShieldSize;
	float2 m_ShieldPosition;

};

#endif