#include "BOMultiballs.h"


BOMultiballs::BOMultiballs()
{
}


BOMultiballs::~BOMultiballs()
{
}

bool BOMultiballs::GetActive()
{
	return m_isActive;
}

void BOMultiballs::SetActive(bool p_isActive)
{
	m_isActive = p_isActive;
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
	BOPowerUpManager::Notify(PUExtraBall, true);
}

void BOMultiballs::Deactivate()
{
	BOPowerUpManager::Notify(PUExtraBall, false);
}