#include "BOBall.h"

BOBall::BOBall()
{
}


BOBall::~BOBall()
{
}

void BOBall::Update()
{
	m_position.x = m_speed * m_direction.x + m_position.x;
	m_position.y = m_speed * m_direction.y + m_position.y;
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