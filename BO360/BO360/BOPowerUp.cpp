#include "BOPowerUp.h"


BOPowerUp::BOPowerUp()
{
}


BOPowerUp::~BOPowerUp()
{
}

bool BOPowerUp::Initialize(PowerUpTypes p_type, float2 p_position, int2 p_size, std::string p_fileName, float p_speed, int2 p_windowSize)
{
	if (!BOObject::Initialize(p_position, p_size, p_fileName))
	{
		return false;
	}

	m_type = p_type;
	m_hasSpawned = true;
	m_speed = p_speed;
	m_windowSize = p_windowSize;
	m_hasActivated = false;

	// Set direction to center of screen
	m_direction.x = (m_windowSize.x / 2.0f) - m_position.x;
	m_direction.y = (m_windowSize.y / 2.0f) - m_position.y;
	m_direction.normalize();

	return true;
}

void BOPowerUp::Shutdown()
{
}

void BOPowerUp::Draw()
{
	BOGraphicInterface::DrawEx(m_sprite, int4(0,0,40,40), int4(m_position.x,m_position.y,m_size.x,m_size.y), 0.0, int2(0,0));
}


void BOPowerUp::Update(double p_deltaTime)
{
	if (m_hasSpawned)
	{
		m_position.x = (m_speed * p_deltaTime) * m_direction.x + m_position.x;
		m_position.y = (m_speed * p_deltaTime) * m_direction.y + m_position.y;
	}
}

void BOPowerUp::Activate()
{
	if (!m_hasActivated)
	{
		BOPowerUpManager::Notify(m_type, true);
		m_hasActivated = true;
	}
	
}

void BOPowerUp::Deactivate()
{
	BOPowerUpManager::Notify(m_type, false);
	m_hasActivated = false;
}


bool BOPowerUp::GetActive()
{
	return m_isActive;
}

void BOPowerUp::SetActive(bool p_isActive)
{
	m_isActive = p_isActive;
}

float2 BOPowerUp::GetDirection()
{
	return m_direction;
}

PowerUpTypes BOPowerUp::GetType()
{
	return m_type;
}