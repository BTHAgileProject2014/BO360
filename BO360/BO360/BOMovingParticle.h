#ifndef BOMOVINGPARTICLE_H_
#define BOMOVINGPARTICLE_H_

#include "BOObject.h"

class BOMovingParticle : public BOObject
{
public:
	BOMovingParticle();
	~BOMovingParticle();

	bool Initialize(ParticleType p_type, Uint32 p_timeMS, float2 p_position, int2 p_size, bool p_rotate, float p_rotation, float p_angleIncrement, float2 p_direction, float p_speed);
	bool Update(Uint32 p_deltaTime);
	void Draw();

	bool IsDead();

private:
	ParticleType m_type;
	Uint32 m_timeLeftMS;

	bool m_rotate;
	float m_rotation;
	float m_angleIncrement;
	
	int m_direction;
	float m_speed;

	bool m_dead;
};
#endif