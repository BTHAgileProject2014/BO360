#include "BOParticleSystem.h"

BOParticleSystem::BOParticleSystem()
{

}

BOParticleSystem::~BOParticleSystem()
{

}

bool BOParticleSystem::Initialize(int p_maxParticles)
{
	bool l_result = true;

	// Empty all the lists.
	m_movingParticleList.clear();
	m_stationaryParticleList.clear();

	// Define sizes.
	m_sizes[BALLTRAIL] = int2(10, 10);
	m_sizes[BALLDEBRIS] = int2(20, 20);
	m_sizes[BLOCKDEBRIS] = int2(20, 20);
	m_sizes[EXPLOSION] = int2(8, 8);
	m_sizes[POWERUPDEBRIS] = int2(5, 5);
	m_sizes[DEBUGTRAIL] = int2(3, 3);

	m_maxParticles = p_maxParticles;
	m_currentParticles = 0;

	// Initialize all the textures. PREFERABLY IN THE ENUM ORDER!
	m_ballTrailTexture = BOTextureManager::GetTexture(TEXBALLTRAIL);
	if (m_ballTrailTexture == NULL)
	{
		std::cout << "Failed to load 'Ball Trail' particle texture!" << std::endl;
		l_result = false;
	}

	m_ballDebrisTexture = BOTextureManager::GetTexture(TEXBALLDEBRIS);
	if (m_ballDebrisTexture == NULL)
	{
		std::cout << "Failed to load 'Ball Debris' particle texture!" << std::endl;
		l_result = false;
	}

	m_blockDebrisTexture = BOTextureManager::GetTexture(TEXBLOCKDEBRIS);
	if (m_blockDebrisTexture == NULL)
	{
		std::cout << "Failed to load 'Block Debris' particle texture!" << std::endl;
		l_result = false;
	}

	m_explosionTexture = BOTextureManager::GetTexture(TEXEXPLOSION);
	if (m_explosionTexture == NULL)
	{
		std::cout << "Failed to load 'Explosion' particle texture!" << std::endl;
		l_result = false;
	}

	m_powerUpDebrisTexture = BOTextureManager::GetTexture(TEXPUDEBRIS);
	if (m_powerUpDebrisTexture == NULL)
	{
		std::cout << "Failed to load 'Power Up Debris' particle texture!" << std::endl;
		l_result = false;
	}

	m_debugTrailTexture = BOTextureManager::GetTexture(TEXDEBUGTRAIL);
	if (m_debugTrailTexture == NULL)
	{
		std::cout << "Failed to load 'Debug Trail' particle texture!" << std::endl;
		l_result = false;
	}

	return l_result;
}

void BOParticleSystem::Shutdown()
{

	m_movingParticleList.clear();
	m_movingParticleList.shrink_to_fit();

	m_stationaryParticleList.clear();
	m_stationaryParticleList.shrink_to_fit();
}

// Add a moving particle to the system.
void BOParticleSystem::AddMovingParticle(ParticleType p_type, double p_timeS, float2 p_position, bool p_rotate, float p_rotation, float p_angleIncrement, float2 p_direction, float p_speed)
{
	if (m_currentParticles < m_maxParticles)
	{
		int2 l_size;
		BOMovingParticle l_particle;

		// Set correct size
		switch (p_type)
		{
		case(BALLTRAIL) : { l_size = m_sizes[BALLTRAIL];  break; }
		case(BALLDEBRIS) : { l_size = m_sizes[BALLDEBRIS];  break; }
		case(BLOCKDEBRIS) : { l_size = m_sizes[BLOCKDEBRIS];  break; }
		case(EXPLOSION) : { l_size = m_sizes[EXPLOSION];  break; }
		case(POWERUPDEBRIS) : { l_size = m_sizes[POWERUPDEBRIS];  break; }
		case(DEBUGTRAIL) : { l_size = m_sizes[DEBUGTRAIL];  break; }
		}

		l_particle.Initialize(p_type, p_timeS, p_position, l_size, p_rotate, p_rotation, p_angleIncrement, p_direction, p_speed);

		m_movingParticleList.push_back(l_particle);

		m_currentParticles++;
	}
}

// Add a particle that does not move to the system.
void BOParticleSystem::AddStationaryParticle(ParticleType p_type, double p_timeS, float2 p_position, bool p_rotate, float p_rotation, float p_angleIncrement)
{
	if (m_currentParticles < m_maxParticles)
	{
		int2 l_size;
		BOStationaryParticle l_particle;

		// Set correct size
		switch (p_type)
		{
		case(BALLTRAIL) : { l_size = m_sizes[BALLTRAIL];  break; }
		case(BALLDEBRIS) : { l_size = m_sizes[BALLDEBRIS];  break; }
		case(BLOCKDEBRIS) : { l_size = m_sizes[BLOCKDEBRIS];  break; }
		case(EXPLOSION) : { l_size = m_sizes[EXPLOSION];  break; }
		case(POWERUPDEBRIS) : { l_size = m_sizes[POWERUPDEBRIS];  break; }
		case(DEBUGTRAIL) : { l_size = m_sizes[DEBUGTRAIL];  break; }
		}

		l_particle.Initialize(p_type, p_timeS, p_position, l_size, p_rotate, p_rotation, p_angleIncrement);

		m_stationaryParticleList.push_back(l_particle);

		m_currentParticles++;
	}
}

void BOParticleSystem::Update(double p_deltaTime)
{
	// Clean the lists from dead particles.
	CleanLists();

	// Update moving particles.
	for (unsigned int i = 0; i < m_movingParticleList.size(); i++)
	{
		m_movingParticleList[i].Update(p_deltaTime);
	}

	// Update stationary particles.
	for (unsigned int i = 0; i < m_stationaryParticleList.size(); i++)
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
			m_currentParticles--;
		}
	}

	// Remove stationary particles if they are to old.
	for (int i = (m_stationaryParticleList.size() - 1); i > -1; i--)
	{
		if (m_stationaryParticleList[i].IsDead())
		{
			m_stationaryParticleList.erase(m_stationaryParticleList.begin() + i);
			m_currentParticles--;
		}
	}
}

void BOParticleSystem::DrawParticles()
{
	// Draw all moving particles.
	for (unsigned int i = 0; i < m_movingParticleList.size(); i++)
	{
		m_movingParticleList[i].Draw(GetTexture(m_movingParticleList[i].GetType()));
	}

	// Draw all stationary particles.
	for (unsigned int i = 0; i < m_stationaryParticleList.size(); i++)
	{
		m_stationaryParticleList[i].Draw(GetTexture(m_stationaryParticleList[i].GetType()));
	}
}

SDL_Texture* BOParticleSystem::GetTexture(ParticleType p_type)
{
	switch (p_type)
	{
		case BALLTRAIL:
		{
			return m_ballTrailTexture;
		}
		
		case BALLDEBRIS:
		{
			return m_ballDebrisTexture;
		}

		case BLOCKDEBRIS:
		{
			return m_blockDebrisTexture;
		}

		case EXPLOSION:
		{
			return m_explosionTexture;
		}

		case POWERUPDEBRIS:
		{
			return m_powerUpDebrisTexture;
		}

		case DEBUGTRAIL:
		{
			return m_debugTrailTexture;
		}

		default:
		{
			std::cout << "An unhandled particle type was detected! (BOParticleSystem.cpp, GetTexture() function)" << std::endl;
			break;
		}
	}

	return NULL;
}

void BOParticleSystem::BallDebugTrail(float2 p_position)
{
	float2 l_position = p_position;
	l_position.x -= (m_sizes[DEBUGTRAIL].x / 2);
	l_position.y -= (m_sizes[DEBUGTRAIL].y / 2);

	AddStationaryParticle(DEBUGTRAIL, 2.0f, l_position, false, 0, 0);
}

void BOParticleSystem::BallTrail(float2 p_position)
{
	float2 l_position = p_position;
	l_position.x -= (m_sizes[BALLTRAIL].x / 2);
	l_position.y -= (m_sizes[BALLTRAIL].y / 2);
	l_position.x += rand() % PARTICLEPOSITIONOFFSET - (PARTICLEPOSITIONOFFSET / 2);
	l_position.y += rand() % PARTICLEPOSITIONOFFSET - (PARTICLEPOSITIONOFFSET / 2);

	int l_rotation = rand() % PARTICLEROTATIONVARIATION - (PARTICLEROTATIONVARIATION / 2);

	AddStationaryParticle(BALLTRAIL, 1.0f, l_position, true, (float)l_rotation, (float)l_rotation);
}

void BOParticleSystem::RegularBlockExplosion(float2 p_position)
{
	int l_parts = rand() % BLOCKDEBIRSPEREXPLOSION.x + BLOCKDEBIRSPEREXPLOSION.y;
	for (int p = 0; p < l_parts; p++)
	{
		int l_angle = rand() % PARTICLEROTATIONVARIATION - (PARTICLEROTATIONVARIATION / 2);
		int l_speed = rand() % PARTICLESEXPLOSIONSPEED.x + PARTICLESEXPLOSIONSPEED.y;

		float2 l_position = p_position;
		float2 l_direction = float2(1 * sin((float)l_angle), 1 * cos((float)l_angle));

		AddMovingParticle(BLOCKDEBRIS, 0.25f, l_position, true, (float)l_angle, (float)l_angle, l_direction, (float)l_speed);
	}

	int l_explosions = rand() % EXPLOSIONS.x + EXPLOSIONS.y;
	for (int e = 0; e < l_explosions; e++)
	{
		int l_angle = rand() % PARTICLEROTATIONVARIATION - (PARTICLEROTATIONVARIATION / 2);
		int l_speed = rand() % PARTICLESEXPLOSIONSPEED.x + PARTICLESEXPLOSIONSPEED.y;

		float2 l_position = p_position;
		float2 l_direction = float2(1 * sin((float)l_angle), 1 * cos((float)l_angle));

		AddMovingParticle(EXPLOSION, 0.15f, l_position, false, (float)l_angle, 0.0f, l_direction, (float)l_speed);
	}
}