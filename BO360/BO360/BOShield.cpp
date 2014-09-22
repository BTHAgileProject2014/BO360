#include "BOShield.h"


BOShield::BOShield()
{
}


BOShield::~BOShield(){}

bool BOShield::Initialize(int2 p_ShieldSize, std::string p_ShieldFN, int2 p_WindowSize)
{
	m_WindowSize = p_WindowSize;
	m_IsActive = false;
	m_ShieldSprite = NULL;

	m_ShieldSphere.pos.x = m_WindowSize.x / 2.0f;
	m_ShieldSphere.pos.y = m_WindowSize.y / 2.0f;
	m_ShieldSphere.radius = p_ShieldSize.x / 2;
	m_ShieldSize = p_ShieldSize;

	m_ShieldSprite = BOGraphicInterface::LoadTexture(p_ShieldFN);

	return true;
}
void BOShield::Shutdown()
{
	SDL_DestroyTexture(m_ShieldSprite);
	m_ShieldSprite = NULL;
}
int BOShield::Update(Uint32 p_deltaTime, sphere p_Ball)
{
	int bounceResult = 0;
	if (m_IsActive)
	{
		bounceResult = BOPhysics::CheckCollisionBallShield(p_Ball, m_ShieldSphere);
		if (bounceResult != 0)
		{
			m_IsActive = false;
		}
	}
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

