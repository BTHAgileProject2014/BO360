#include "BOBall.h"

BOBall::BOBall()
{
}


BOBall::~BOBall()
{
}

bool BOBall::Initialize(float2 p_position, int2 p_size, std::string p_fileName, float p_speed, float2 p_direction, int2 p_windowSize)
{
	m_canColide = true;
	m_position = p_position;
	m_size = p_size;
	m_speed = p_speed;
	m_direction = p_direction.normalized();
	m_windowSize = p_windowSize;

	// Load texture.
	m_sprite = BOGraphicInterface::LoadTexture(p_fileName);

	m_mouseCheat = false;

	return true;
}

void BOBall::Update(Uint32 p_deltaTime)
{
	if (m_mouseCheat)
	{
		return;
	}

	m_position.x = (m_speed * p_deltaTime) * m_direction.x + m_position.x;
	m_position.y = (m_speed * p_deltaTime) * m_direction.y + m_position.y;

	if (m_position.x < (m_size.x / 2) || m_position.x > (m_windowSize.x - (m_size.x / 2)))
	{
		m_canColide = true;
		m_direction.x *= -1;
	}
	if (m_position.y < (m_size.y / 2) || m_position.y > (m_windowSize.y - (m_size.y / 2)))
	{
		m_canColide = true;
		m_direction.y *= -1;
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
	m_canColide = false;
}
void BOBall::BouncedOnHexa()
{
	m_canColide = true;
}

box BOBall::GetBoundingBox()
{
	return box(m_position, m_size);
}

void BOBall::Handle(InputMessages p_inputMessages)
{
	if (p_inputMessages.spacebarKey)
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
		m_position.x = p_inputMessages.mouseX;
		m_position.y = p_inputMessages.mouseY;
	}
}

void BOBall::BouncedOnHexagon()
{
	m_canColide = true;
}
