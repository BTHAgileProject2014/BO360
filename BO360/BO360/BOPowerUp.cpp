#include "BOPowerUp.h"


BOPowerUp::BOPowerUp()
{
}


BOPowerUp::~BOPowerUp()
{
}

bool BOPowerUp::Initialize(PowerUpTypes p_type, float2 p_position, int2 p_size, std::string p_fileName, float p_speed, int2 p_windowSize, BOPaddle* p_paddle, float2 p_blackholePosition)
{
	if (!BOObject::Initialize(p_position, p_size, p_fileName))
	{
		return false;
	}

	m_type = p_type;
	m_speed = p_speed;
	m_windowSize = p_windowSize;
	m_hasActivated = false;
	m_paddle = p_paddle;
	m_blackholePosition = p_blackholePosition;

	// Set direction towards blackhole
	m_direction.x = m_blackholePosition.x - m_position.x;
	m_direction.y = m_blackholePosition.y - m_position.y;
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
	// Move the powerup towards the blackhole
	m_position.x = (m_speed * p_deltaTime) * m_direction.x + m_position.x;
	m_position.y = (m_speed * p_deltaTime) * m_direction.y + m_position.y;

	// Checks powerup "ball" against the pad, if colliding with pad do powerup effect and remove the powerup"ball"
	float2 result = BOPhysics::BallPadCollision(GetBoundingSphere(), m_direction, m_paddle->GetBoundingSphere(), m_paddle->GetRotation() - 10.6, m_paddle->GetDegrees());
	if (!(result.x == 0 && result.y == 0))
	{
		// Play  sound for PowerUp catched
		BOSoundManager::PlaySound(SOUND_POWERUP);
		
		Activate();
		BOPowerUpManager::RemovePowerUp(this);
	}
	// Check if the powerup "ball" is inside the black hole
	else if (BOPhysics::CollisionRadiusRadius(GetBoundingSphere().pos, GetBoundingSphere().radius, m_blackholePosition, 1))
	{
		BOPowerUpManager::RemovePowerUp(this);
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