#include "BOBall.h"

BOBall::BOBall()
{
}


BOBall::~BOBall()
{
}

bool BOBall::Initialize(float2 p_position, int2 p_size, std::string p_fileName, float p_speed, float2 p_direction)
{
	m_canColide = false;
	m_position = p_position;
	m_size = p_size;
	m_speed = p_speed;
	m_direction = p_direction.normalized();

	// Load texture.
	m_sprite = BOGraphicInterface::LoadTexture(p_fileName);

	return true;
}

void BOBall::Update()
{
	m_position.x = m_speed * m_direction.x + m_position.x;
	m_position.y = m_speed * m_direction.y + m_position.y;

	if (m_position.x < 20 || m_position.x > 780)
	{
		m_canColide = true;
		m_direction.x *= -1;
	}
	if (m_position.y < 20 || m_position.y > 580)
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
	m_direction = p_direction.normalized();
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

box BOBall::GetBoundingBox()
{
	return box(m_position, m_size);
}
