#include "BOParticleSystem.h"

BOParticleSystem::BOParticleSystem()
{

}

BOParticleSystem::~BOParticleSystem()
{

}

bool BOParticleSystem::Initialize()
{
	bool l_result = true;

	// Empty all the lists.
	m_movingParticleList.clear();
	m_stationaryParticleList.clear();
	m_textures.clear();

	// Define sizes.
	m_sizes[BALLTRAIL] = int2(10, 10);
	m_sizes[BALLDEBRIS] = int2(5, 5);
	m_sizes[BLOCKDEBRIS] = int2(10, 10);
	m_sizes[POWERUPDEBRIS] = int2(5, 5);

	// Initialize all the textures. PREFERABLY IN THE ENUM ORDER!
	m_textures.push_back(BOGraphicInterface::LoadTexture("Bilder/Particles/BallTrail.png"));
	if (m_textures[m_textures.size()] == NULL)
	{
		std::cout << "Failed to load 'Ball Trail' particle texture!" << std::endl;
		l_result = false;
	}

	m_textures.push_back(BOGraphicInterface::LoadTexture("Bilder/Particles/BallDebris.png"));
	if (m_textures[m_textures.size()] == NULL)
	{
		std::cout << "Failed to load 'Ball Debris' particle texture!" << std::endl;
		l_result = false;
	}

	m_textures.push_back(BOGraphicInterface::LoadTexture("Bilder/Particles/BlockDebris.png"));
	if (m_textures[m_textures.size()] == NULL)
	{
		std::cout << "Failed to load 'Block Debris' particle texture!" << std::endl;
		l_result = false;
	}

	m_textures.push_back(BOGraphicInterface::LoadTexture("Bilder/Particles/PowerUpDebris.png"));
	if (m_textures[m_textures.size()] == NULL)
	{
		std::cout << "Failed to load 'Power Up Debris' particle texture!" << std::endl;
		l_result = false;
	}

	return l_result;
}

void BOParticleSystem::Shutdown()
{
	for (int i = 0; i < m_textures.size(); i++)
	{
		BOGraphicInterface::DestroyTexture(m_textures[i]);
	}

	m_textures.clear();
	m_textures.shrink_to_fit();

	m_movingParticleList.clear();
	m_movingParticleList.shrink_to_fit();

	m_stationaryParticleList.clear();
	m_stationaryParticleList.shrink_to_fit();
}

// Add a moving particle to the system.
void BOParticleSystem::AddMovingParticle(ParticleType p_type, Uint32 p_timeMS, float2 p_position, bool p_rotate, float p_rotation, float p_angleIncrement, float2 p_direction, float p_speed)
{
	int2 l_size;
	BOMovingParticle l_particle;

	// Set correct size
	switch (p_type)
	{
		case(BALLTRAIL) :		{ l_size = m_sizes[BALLTRAIL];  break; }
		case(BALLDEBRIS) :		{ l_size = m_sizes[BALLDEBRIS];  break; }
		case(BLOCKDEBRIS) :		{ l_size = m_sizes[BLOCKDEBRIS];  break; }
		case(POWERUPDEBRIS) :	{ l_size = m_sizes[POWERUPDEBRIS];  break; }
	}

	l_particle.Initialize(p_type, p_timeMS, p_position, l_size, p_rotate, p_rotation, p_angleIncrement, p_direction, p_speed);

	m_movingParticleList.push_back(l_particle);
}

// Add a particle that does not move to the system.
void BOParticleSystem::AddStationaryParticle(ParticleType p_type, Uint32 p_timeMS, float2 p_position, bool p_rotate, float p_rotation, float p_angleIncrement)
{
	int2 l_size;
	BOStationaryParticle l_particle;

	// Set correct size
	switch (p_type)
	{
		case(BALLTRAIL) : { l_size = m_sizes[BALLTRAIL];  break; }
		case(BALLDEBRIS) : { l_size = m_sizes[BALLDEBRIS];  break; }
		case(BLOCKDEBRIS) : { l_size = m_sizes[BLOCKDEBRIS];  break; }
		case(POWERUPDEBRIS) : { l_size = m_sizes[POWERUPDEBRIS];  break; }
	}

	l_particle.Initialize(p_type, p_timeMS, p_position, l_size, p_rotate, p_rotation, p_angleIncrement);

	m_stationaryParticleList.push_back(l_particle);
}

void BOParticleSystem::Update(Uint32 p_deltaTime)
{
	// Clean the lists from dead particles.
	CleanLists();

	// Update moving particles.
	for (int i = 0; i < m_movingParticleList.size(); i++)
	{
		m_movingParticleList[i].Update(p_deltaTime);
	}

	// Update stationary particles.
	for (int i = 0; i < m_stationaryParticleList.size(); i++)
	{
		m_stationaryParticleList[i].Update(p_deltaTime);
	}
}

void BOParticleSystem::CleanLists()
{
	// Remove moving particles if they are to old.
	for (int i = (m_movingParticleList.size() - 1); i > -1; i--)
	{
		if (m_movingParticleList[i].IsDead())
		{
			m_movingParticleList.erase(m_movingParticleList.begin() + i);
		}
	}

	// Remove stationary particles if they are to old.
	for (int i = (m_stationaryParticleList.size() - 1); i > -1; i--)
	{
		if (m_stationaryParticleList[i].IsDead())
		{
			m_stationaryParticleList.erase(m_stationaryParticleList.begin() + i);
		}
	}
}

void BOParticleSystem::DrawParticles()
{
	// Draw all moving particles.
	for (int i = 0; i < m_movingParticleList.size(); i++)
	{
		m_movingParticleList[i].Draw(GetTexture(m_movingParticleList[i].GetType()));
	}

	// Draw all stationary particles.
	for (int i = 0; i < m_stationaryParticleList.size(); i++)
	{
		m_stationaryParticleList[i].Draw(GetTexture(m_movingParticleList[i].GetType()));
	}
}

SDL_Texture* BOParticleSystem::GetTexture(ParticleType p_type)
{
	switch (p_type)
	{
		case BALLTRAIL:
		{
			return m_textures[BALLTRAIL];
		}
		
		case BALLDEBRIS:
		{
			return m_textures[BALLDEBRIS];
		}

		case BLOCKDEBRIS:
		{
			return m_textures[BLOCKDEBRIS];
		}

		case POWERUPDEBRIS:
		{
			return m_textures[POWERUPDEBRIS];
		}

		default:
		{
			std::cout << "An unhandled particle type was deteced! (BOParticleSystem.cpp, GetTexture() function)" << std::endl;
			break;
		}
	}
}