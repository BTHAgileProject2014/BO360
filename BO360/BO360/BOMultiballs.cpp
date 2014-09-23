#include "BOMultiballs.h"


BOMultiballs::BOMultiballs()
{
}


BOMultiballs::~BOMultiballs()
{
}

bool BOMultiballs::Initialize(float2 p_position, int2 p_size, std::string p_fileName, float p_speed, int2 p_windowSize)
{
	m_type = PUExtraBall;
	return BOPowerUp::Initialize(p_position, p_size, p_fileName, p_speed, p_windowSize);
}

void BOMultiballs::SwitchActive()
{
	if (m_isActive) 
	{
		m_isActive = false;
	}
	else
	{
		m_isActive = true;
	}
}

void BOMultiballs::Activate()
{
	if (!m_hasActivated)
	{
		BOPowerUpManager::Notify(PUExtraBall, true);
	}
	m_hasActivated = true;
}

void BOMultiballs::Deactivate()
{
	BOPowerUpManager::Notify(PUExtraBall, false);
	m_hasActivated = false;
}