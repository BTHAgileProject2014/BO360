#ifndef BOSHIELDPU_H_
#define BOSHIELDPU_H_
#include "BOPowerUp.h"
#include "BOPowerUpManager.h"


class BOShieldPU : public BOPowerUp
{
public:
	BOShieldPU();
	~BOShieldPU();

	bool Initialize(float2 p_POPos, int2 p_POSize, std::string p_POFN, float p_POSpeed, int2 p_WindowSize);

	void Activate();
	void Deactivate();


};

#endif