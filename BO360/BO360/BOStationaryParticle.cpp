#include "BOStationaryParticle.h"

BOStationaryParticle::BOStationaryParticle()
{

}

BOStationaryParticle::~BOStationaryParticle()
{

}

void BOStationaryParticle::Initialize(ParticleType p_type, double p_timeS, float2 p_position, int2 p_size, bool p_rotate, float p_rotation, float p_angleIncrement)
{
	m_type = p_type;
	m_timeLeftS = p_timeS;
	m_position = p_position;
	m_size = p_size;

	m_rotate = p_rotate;
	m_angleIncrement = p_angleIncrement;
	m_rotation = p_rotation;
	if (m_rotation > 360)
	{
		m_rotation -= 360;
	}

	m_dead = false;
}

void BOStationaryParticle::Update(double p_deltaTime)
{
	// Rotate if ment to be rotated.
	if (m_rotate)
	{
		m_rotation += (float)(p_deltaTime * m_angleIncrement);

		if (m_rotation > 360)
		{
			m_rotation -= 360;
		}
	}

	// Kill the particle if it runs out of time.
	m_timeLeftS -= p_deltaTime;
	if (m_timeLeftS < 0)
	{
		m_dead = true;
	}
}

void BOStationaryParticle::Draw(SDL_Texture* p_texture)
{
	int4 l_target = int4((int)m_position.x, (int)m_position.y, m_size.x, m_size.y);
	int4 l_source = int4(0, 0, m_size.x, m_size.y);

	BOGraphicInterface::DrawEx(p_texture, l_source, l_target, m_rotation, int2(l_source.z / 2, l_source.w / 2));
}

bool BOStationaryParticle::IsDead()
{
	return m_dead;
}

ParticleType BOStationaryParticle::GetType()
{
	return m_type;
}