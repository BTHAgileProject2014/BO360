#include "BOShield.h"


BOShield::BOShield()
{
	m_IsActive = false;
	m_ShieldSprite = NULL;
}


BOShield::~BOShield(){}

bool BOShield::Initialize(float2 p_ShieldPos, int2 p_ShieldSize, std::string p_ShieldFN,
	float2 p_POPos, int2 p_POSize, std::string p_POFN)
{
	m_ShieldPosition = p_ShieldPos;
	m_ShieldSize = p_ShieldSize;

	m_ShieldSprite = BOGraphicInterface::LoadTexture(p_ShieldFN);
	BOPowerUp::Initialize(p_POPos, p_POSize, p_POFN);

	return true;
}
void BOShield::Update()
{
	

	BOPowerUp::Update();
}
void BOShield::Draw()
{
	if (m_IsActive)
	{
		BOGraphicInterface::Draw(m_ShieldSprite, m_ShieldPosition, m_ShieldSize);
	}
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
