#include "BOPUPadSize.h"


BOPUPadSize::BOPUPadSize()
{
}


BOPUPadSize::~BOPUPadSize()
{
}

bool BOPUPadSize::Initialize(float2 p_position, int2 p_size, std::string p_fileName, float p_speed, int2 p_windowSize)
{
	m_type = PUBiggerPad;
	return BOPowerUp::Initialize(p_position, p_size, p_fileName, p_speed, p_windowSize);
}

void BOPUPadSize::Activate()
{
	if (!m_hasActivated)
	{
		BOPowerUpManager::Notify(PUBiggerPad, true);
	}
	m_hasActivated = true;
}

void BOPUPadSize::Deactivate()
{
	BOPowerUpManager::Notify(PUBiggerPad, false);
	m_hasActivated = false;
}