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
	BOPowerUpManager::Notify(PUExtraBall, true);
}

void BOMultiballs::Deactivate()
{
	BOPowerUpManager::Notify(PUExtraBall, false);
}