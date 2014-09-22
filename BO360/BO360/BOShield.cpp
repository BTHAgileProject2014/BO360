#include "BOShield.h"


BOShield::BOShield()
{
}


BOShield::~BOShield(){}

bool BOShield::Initialize(int2 p_ShieldSize, std::string p_ShieldFN, int2 p_WindowSize)
{
	m_WindowSize = p_WindowSize;
	m_isActive = false;
	m_ShieldSprite = NULL;

	m_ShieldSphere.pos.x = m_WindowSize.x / 2.0f;
	m_ShieldSphere.pos.y = m_WindowSize.y / 2.0f;
	m_ShieldSphere.radius = p_ShieldSize.x / 2;
	m_ShieldSize = p_ShieldSize;

	m_ShieldSprite = BOGraphicInterface::LoadTexture(p_ShieldFN);

	return true;
}
bool BOShield::InitializePU(float2 p_POPos, int2 p_POSize, std::string p_POFN, float p_POSpeed)
{
	BOPowerUp::Initialize(p_POPos, p_POSize, p_POFN, p_POSpeed, m_WindowSize);
	return true;
}
int BOShield::Update(Uint32 p_deltaTime, sphere p_Ball)
{
	int bounceResult = 0;
	if (m_isActive)
	{
		bounceResult = BOPhysics::CheckCollisionBallShield(p_Ball, m_ShieldSphere);
		if (bounceResult != 0)
		{
			Deactivate();
		}
	}

	BOPowerUp::Update(p_deltaTime);
	return bounceResult;
}
void BOShield::Draw()
{
	if (m_isActive)
	{
		BOGraphicInterface::Draw(m_ShieldSprite, m_ShieldSphere.pos, m_ShieldSize);
	}
}
void BOShield::SetActive(bool p_IsActive)
{
	m_isActive = p_IsActive;
}
void BOShield::SwitchActive()
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
bool BOShield::GetActive()
{
	return m_isActive;
}

void BOShield::Activate()
{
	if (!m_isActive)
	{
		BOPowerUpManager::Notify(PUShield, true);
		m_isActive = true;
	}
}

void BOShield::Deactivate()
{
	BOPowerUpManager::Notify(PUShield, false);
	m_isActive = false;
}