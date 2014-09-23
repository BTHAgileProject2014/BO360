#include "BOShieldPU.h"


BOShieldPU::BOShieldPU()
{
}


BOShieldPU::~BOShieldPU()
{
}
bool BOShieldPU::Initialize(float2 p_POPos, int2 p_POSize, std::string p_POFN, float p_POSpeed, int2 p_WindowSize)
{
	m_type = PUShield;
	BOPowerUp::Initialize(p_POPos, p_POSize, p_POFN, p_POSpeed, p_WindowSize);
	return true;
}

void BOShieldPU::Activate()
{
	if (!m_hasActivated)
	{
		BOPowerUpManager::Notify(PUShield, true);
		m_hasActivated = true;
	}
}

void BOShieldPU::Deactivate()
{
	BOPowerUpManager::Notify(PUShield, false);
	m_hasActivated = false;
}