#ifndef BOSHIELD_H_
#define BOSHIELD_H_
#include "BOPowerUp.h"
class BOShield : BOPowerUp
{
public:
	BOShield();
	~BOShield();

	void SetActive(bool p_IsActive);
	void SwitchActive();
	bool GetActive();

private:
	bool m_IsActive;
};

#endif