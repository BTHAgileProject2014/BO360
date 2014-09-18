#include "BOShield.h"


BOShield::BOShield()
{
	m_IsActive = false;
	m_ShieldSprite = NULL;
}


BOShield::~BOShield(){}

bool BOShield::Initialize(int2 p_ShieldSize, int p_ShieldRadius, std::string p_ShieldFN,
	float2 p_POPos, int2 p_POSize, std::string p_POFN, int2 p_WindowSize, float p_POSpeed)
{
	m_ShieldSphere.pos.x = p_WindowSize.x / 2.0f;
	m_ShieldSphere.pos.y = p_WindowSize.y / 2.0f;
	m_ShieldSphere.radius = p_ShieldRadius;
	m_ShieldSize = p_ShieldSize;

	m_ShieldSprite = BOGraphicInterface::LoadTexture(p_ShieldFN);
	BOPowerUp::Initialize(p_POPos, p_POSize, p_POFN, p_POSpeed, p_WindowSize);

	return true;
}
int BOShield::Update(Uint32 p_deltaTime, sphere p_Ball)
{
	int bounceResult;
	if (m_IsActive)
	{
		bounceResult = BOPhysics::CheckCollisionBallShield(p_Ball, m_ShieldSphere);
		if (bounceResult != 0)
		{
			m_IsActive = false;
		}
	}

	BOPowerUp::Update(p_deltaTime);
	return bounceResult;
}
void BOShield::Draw()
{
	if (m_IsActive)
	{
		BOGraphicInterface::Draw(m_ShieldSprite, m_ShieldSphere.pos, m_ShieldSize);
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

void BOShield::Activate()
{
	BOPowerUpManager::Notify(shield, true);
}

void BOShield::Deactivate()
{
	BOPowerUpManager::Notify(shield, false);
}