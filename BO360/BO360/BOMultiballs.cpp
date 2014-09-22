#include "BOMultiballs.h"


BOMultiballs::BOMultiballs()
{
}


BOMultiballs::~BOMultiballs()
{
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
}