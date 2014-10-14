#ifndef BOMOVINGPARTICLE_H_
#define BOMOVINGPARTICLE_H_

#include "BOObject.h"

class BOMovingParticle : public BOObject
{
public:
	BOMovingParticle();
	~BOMovingParticle();

	void Initialize(ParticleType p_type, double p_timeS, float2 p_position, int2 p_size, bool p_rotate, float p_rotation, float p_angleIncrement, float2 p_direction, float p_speed);
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
	
	float2 m_direction;
	float m_speed;

	bool m_dead;
    Uint8 m_opacity;

    double m_startFadeTime;
};
#endif