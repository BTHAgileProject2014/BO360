#ifndef BOSTATIONARYPARTICLE_H_
#define BOSTATIONARYPARTICLE_H_

#include "BOObject.h"

class BOStationaryParticle : public BOObject
{
public:
	BOStationaryParticle();
	~BOStationaryParticle();

	void Initialize(ParticleType p_type, double p_timeS, float2 p_position, int2 p_size, bool p_rotate, float p_rotation, float p_angleIncrement);
	void Update(double p_deltaTime);
	void Draw(SDL_Texture* p_texture);

	bool IsDead();
	ParticleType GetType();

private:
	ParticleType m_type;
	double m_timeLeftS;

	bool m_rotate;
	float m_rotation;
	float m_angleIncrement;
   
	bool m_dead;
    double m_startFadeTime;
};
#endif