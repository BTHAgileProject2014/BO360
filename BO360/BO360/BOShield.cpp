#include "BOShield.h"


BOShield::BOShield()
{
	m_IsActive = false;
}


BOShield::~BOShield()
{
}

void BOShield::SetActive(bool p_IsActive)
{
	m_IsActive = p_IsActive;
}
void BOShield::SwitchActive()
{
	if (m_IsActive)
	{
		m_IsActive = false;
	}
	else
	{
		m_IsActive = true;
	}
}
bool BOShield::GetActive()
{
	return m_IsActive;
}