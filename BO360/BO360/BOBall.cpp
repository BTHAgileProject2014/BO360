#include "BOBall.h"

BOBall::BOBall()
{

}

BOBall::~BOBall()
{

}

bool BOBall::Initialize(float2 p_position, int2 p_size, SDL_Texture* p_sprite, float p_speed, float2 p_direction, int2 p_windowSize)
{
    if (!BOObject::Initialize(p_position, p_size, p_sprite))
	{
		return false;
	}
	m_damage = 10000;
	m_Fuel = 0.0f;
	m_canColide = true;
	m_speed = p_speed;
	m_direction = p_direction.normalized();
	m_windowSize = p_windowSize;
	m_stuckToPad = true;
	
	// Load texture.
	m_sprite = p_sprite;
	m_sprite2 = BOTextureManager::GetTexture(TEXDEBUGBALL);
	m_sprite3 = m_sprite;

	m_mouseCheat = false;

	return true;
}

void BOBall::Update(double p_deltaTime, sphere p_blackHoleBounds)
{
	if (!m_stuckToPad && !m_mouseCheat)
	{
		Move(p_deltaTime, p_blackHoleBounds);
	}
}

void BOBall::SetSpeed(float p_speed)
{
	m_speed = p_speed;
}

float BOBall::GetSpeed()
{
	return m_speed;
}

void BOBall::SetDirection(float2 p_direction)
{
	if (!(p_direction.x == 0 && p_direction.y == 0))
	{
		m_direction = p_direction.normalized();
	}
}

float2 BOBall::GetDirection()
{
	return m_direction;
}

bool BOBall::CanColide()
{
	return m_canColide;
}

void BOBall::BouncedOnPad()
{
	m_Fuel = 5.0f;
}

box BOBall::GetBoundingBox()
{
	return box(m_position, m_size);
}

void BOBall::Handle(InputMessages p_inputMessages)
{
	if (p_inputMessages.upArrow)
	{
		if (m_mouseCheat)
		{
			m_mouseCheat = false;
		}
		else
		{
			m_mouseCheat = true;
		}
	}
	if (m_mouseCheat)
	{
		m_position.x = (float)p_inputMessages.mouseX;
		m_position.y = (float)p_inputMessages.mouseY;
	}
}

void BOBall::BouncedOnHexagon()
{
	m_canColide = true;
}

float BOBall::GetFuel()
{
	return m_Fuel;
}
void BOBall::SetFuel(float p_fuel)
{
	m_Fuel = p_fuel;
}

int BOBall::GetDamage()
{
	return m_damage;
}

bool BOBall::IsStuckToPad()
{
	return m_stuckToPad;
}

void BOBall::SetStuckToPad(bool p_stuck)
{
	m_stuckToPad = p_stuck;
}

void BOBall::Move(double p_deltaTime, sphere p_blackHoleBounds)
{
	if (m_Fuel > 0)
	{
		m_position.x = (float)(m_speed * p_deltaTime) * m_direction.x + m_position.x;
		m_position.y = (float)(m_speed * p_deltaTime) * m_direction.y + m_position.y;
		m_sprite = m_sprite2;
		m_Fuel -= (float)p_deltaTime;
	}
	else
	{
		m_position.x = (float)(0.75*m_speed * p_deltaTime) * m_direction.x + m_position.x;
		m_position.y = (float)(0.75*m_speed * p_deltaTime) * m_direction.y + m_position.y;
		m_sprite = m_sprite3;
		SetDirection(BOPhysics::BlackHoleGravity(GetBoundingSphere(), GetDirection(), GetSpeed(), p_blackHoleBounds, p_deltaTime));
	}

	if (m_position.x < (m_size.x / 2) || m_position.x >(m_windowSize.x - (m_size.x / 2)))
	{
		m_Fuel = 0;
		m_canColide = true;
		m_direction.x *= -1;
	}
	if (m_position.y < (m_size.y / 2) || m_position.y >(m_windowSize.y - (m_size.y / 2)))
	{
		m_Fuel = 0;
		m_canColide = true;
		m_direction.y *= -1;
	}
}

void BOBall::SetPosition(float2 p_position)
{
	if (m_stuckToPad)
	{
		int2 windowSize = BOGraphicInterface::GetWindowSize();
		m_direction = p_position - float2((windowSize.x * 0.5f), (windowSize.y *0.5f));
		m_direction.normalize();
		p_position.x += m_direction.x * 6;
		p_position.y += m_direction.y * 6;
	}
	BOObject::SetPosition(p_position);
}