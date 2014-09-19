#include "BOPowerUp.h"


BOPowerUp::BOPowerUp()
{
}


BOPowerUp::~BOPowerUp()
{
}

bool BOPowerUp::Initialize(float2 p_position, int2 p_size, std::string p_fileName, float p_speed, int2 p_windowSize)
{
	m_hasSpawned = true;
	m_speed = p_speed;
	m_windowSize = p_windowSize;

	// Set direction to center of screen
	m_direction.x = (p_windowSize.x / 2.0f) - m_position.x;
	m_direction.y = (p_windowSize.y / 2.0f) - m_position.y;
	m_direction = m_direction.normalized();

	return BOObject::Initialize(p_position, p_size, p_fileName);
}

void BOPowerUp::Shutdown()
{
}

void BOPowerUp::Draw()
{
	BOObject::Draw();
}

void BOPowerUp::Update(Uint32 p_delaTime)
{
	if (m_hasSpawned)
	{
		m_position.x = m_speed * m_direction.x + m_position.x;
		m_position.y = m_speed * m_direction.y + m_position.y;
	}
}

void BOPowerUp::Activate()
{
}

void BOPowerUp::Deactivate()
{
}