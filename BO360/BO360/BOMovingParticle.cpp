#include "BOMovingParticle.h"

BOMovingParticle::BOMovingParticle()
{

}

BOMovingParticle::~BOMovingParticle()
{

}

void BOMovingParticle::Initialize(ParticleType p_type, Uint32 p_timeMS, float2 p_position, int2 p_size, bool p_rotate, float p_rotation, float p_angleIncrement, float2 p_direction, float p_speed)
{
	m_type = p_type;
	m_timeLeftMS = p_timeMS;
	m_position = p_position;
	m_size = p_size;

	m_rotate = p_rotate;
	m_angleIncrement = p_angleIncrement;
	m_rotation = p_rotation;
	if (m_rotation > 360)
	{
		m_rotation -= 360;
	}

	m_direction = p_direction.normalized();
	m_speed = p_speed;

	m_dead = false;
}

void BOMovingParticle::Update(Uint32 p_deltaTime)
{
	// Rotate if ment to be rotated.
	if (m_rotate)
	{
		m_rotation += (p_deltaTime * m_angleIncrement);

		if (m_rotation > 360)
		{
			m_rotation -= 360;
		}
	}
	
	// Update position.
	m_position.x = (m_speed * p_deltaTime) * m_direction.x + m_position.x;
	m_position.y = (m_speed * p_deltaTime) * m_direction.y + m_position.y;

	// Kill the particle if it runs out of time.
	m_timeLeftMS -= p_deltaTime;
	if (m_timeLeftMS < 0)
	{
		m_dead = true;
	}
}

void BOMovingParticle::Draw(SDL_Texture* p_texture)
{
	int4 l_source = int4(m_position.x, m_position.y, m_size.x, m_size.y);
	int4 l_target = l_source;

	BOGraphicInterface::DrawEx(p_texture, l_source, l_target, m_rotation, int2(l_source.z / 2, l_source.w / 2));
}

bool BOMovingParticle::IsDead()
{
	return m_dead;
}

ParticleType BOMovingParticle::GetType()
{
	return m_type;
}