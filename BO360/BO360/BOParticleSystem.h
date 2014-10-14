#ifndef BOPARTICLESYSTEM_H_
#define BOPARTICLESYSTEM_H_

#include "BOComponent.h"
#include "BOUtility.h"
#include "BOMovingParticle.h"
#include "BOStationaryParticle.h"
#include "BOGraphicInterface.h"
#include "BOPhysics.h"
#include <SDL.h>
#include <vector>

#define MAXPARTICLES 5000
#define PARTICLEPOSITIONOFFSET 11
#define PARTICLEROTATIONVARIATION 361
#define PARTICLESEXPLOSIONSPEED int2(200, 100) // MAX, MIN
#define BLOCKDEBIRSPEREXPLOSION int2(6, 2) // MAX, MIN
#define EXPLOSIONS int2(30, 20) // MAX, MIN

class BOParticleSystem : public BOComponent
{
public:
	BOParticleSystem();
	~BOParticleSystem();

	void BallDebugTrail(float2 p_position);
	void BallTrail(float2 p_position);
	void RegularBlockExplosion(float2 p_position);

	bool Initialize(int p_maxParticles);
	void Shutdown();

	void Update(double p_deltaTime);
	void DrawParticles();

private:
	void AddMovingParticle(ParticleType p_type, double p_timeS, float2 p_position, bool p_rotate, float p_rotation, float p_angleIncrement, float2 p_direction, float p_speed);
	void AddStationaryParticle(ParticleType p_type, double p_timeS, float2 p_position, bool p_rotate, float p_rotation, float p_angleIncrement);

	void CleanLists();
	SDL_Texture* GetTexture(ParticleType p_type);

	std::vector<BOMovingParticle> m_movingParticleList;
	std::vector<BOStationaryParticle> m_stationaryParticleList;

	SDL_Texture* m_ballTrailTexture;
	SDL_Texture* m_ballDebrisTexture;
	SDL_Texture* m_blockDebrisTexture;
	SDL_Texture* m_explosionTexture;
	SDL_Texture* m_powerUpDebrisTexture;
	SDL_Texture* m_debugTrailTexture;

	int2 m_sizes[m_numberOfParticleTypes];

	int m_maxParticles;
	int m_currentParticles;

};
#endif