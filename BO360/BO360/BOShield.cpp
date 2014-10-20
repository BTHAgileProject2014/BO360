#include "BOShield.h"

BOShield::BOShield()
{

}

BOShield::~BOShield()
{

}

bool BOShield::Initialize(int2 p_ShieldSize, SDL_Texture* p_sprite, int2 p_WindowSize)
{
	m_WindowSize = p_WindowSize;
	m_IsActive = false;
	if (BOTechTreeEffects::PUEffects.startShield)
	{
		m_IsActive = true;
	}
	m_ShieldSprite = NULL;

	m_ShieldSphere.pos.x = m_WindowSize.x / 2.0f;
	m_ShieldSphere.pos.y = m_WindowSize.y / 2.0f;
	m_ShieldSphere.radius = p_ShieldSize.x / 2.0f;
	m_ShieldSize = p_ShieldSize;
    m_opacity = 255;

	m_ShieldSprite = p_sprite;
	m_lifes = 1 + BOTechTreeEffects::PUEffects.shieldCharge;

	return true;
}

void BOShield::Shutdown()
{
	m_ShieldSprite = NULL;
}

void BOShield::Update(double p_deltaTime, BOBall& p_ball)
{
    if (m_IsActive)
    {
        if (BOPhysics::BallToSphereCollision(p_ball, m_ShieldSphere))
        {
            // Set fuel when the ball have bounced on the pad
            p_ball.BouncedOnPad();

            m_lifes--;
            if (m_lifes <= 0)
            {
                m_IsActive = false;
            }
        }
    }
}

void BOShield::Draw()
{
	if (m_IsActive)
	{
		BOGraphicInterface::Draw(m_ShieldSprite, m_ShieldSphere.pos, m_ShieldSize, m_opacity);
	}
}

void BOShield::SetActive(bool p_IsActive)
{
	m_IsActive = p_IsActive;
	m_lifes += 1 + BOTechTreeEffects::PUEffects.shieldCharge;
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

void BOShield::AddLife(unsigned int p_lifes)
{
	m_lifes += p_lifes;
}

int BOShield::GetLifes()
{
	return m_lifes;
}