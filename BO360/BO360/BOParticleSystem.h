#ifndef BOPARTICLESYSTEM_H_
#define BOPARTICLESYSTEM_H_

#include "BOComponent.h"
#include "BOUtility.h"
#include "BOMovingParticle.h"
#include "BOStationaryParticle.h"
#include "BOGraphicInterface.h"
#include <SDL.h>
#include <vector>

class BOParticleSystem : public BOComponent
{
public:
	BOParticleSystem();
	~BOParticleSystem();

	bool Initialize();
	void Shutdown();

	void AddMovingParticle(ParticleType p_type, Uint32 p_timeMS, float2 p_position, bool p_rotate, float p_rotation, float p_angleIncrement, float2 p_direction, float p_speed);
	void AddStationaryParticle(ParticleType p_type, Uint32 p_timeMS, float2 p_position, bool p_rotate, float p_rotation, float p_angleIncrement);

	void Update(Uint32 p_deltaTime);
	void DrawParticles();

private:
	void CleanLists();
	SDL_Texture* GetTexture(ParticleType p_type);

	std::vector<BOMovingParticle> m_movingParticleList;
	std::vector<BOStationaryParticle> m_stationaryParticleList;

	std::vector<SDL_Texture*> m_textures;
	int2 m_sizes[m_numberOfParticleTypes];
};
#endif