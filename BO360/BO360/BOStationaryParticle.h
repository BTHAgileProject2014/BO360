#ifndef BOSTATIONARYPARTICLE_H_
#define BOSTATIONARYPARTICLE_H_

#include "BOObject.h"

class BOStationaryParticle : public BOObject
{
public:
	BOStationaryParticle();
	~BOStationaryParticle();

	bool Initialize(ParticleType p_type, Uint32 p_timeMS, float2 p_position, int2 p_size, bool p_rotate, float p_rotation, float p_angleIncrement);
	bool Update(Uint32 p_deltaTime);
	void Draw();

	bool IsDead();

private:
	ParticleType m_type;
	Uint32 m_timeLeftMS;

	bool m_rotate;
	float m_rotation;
	float m_angleIncrement;

	bool m_dead;
};
#endif