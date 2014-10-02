#include "BOKeyManager.h"


BOKeyManager::BOKeyManager()
{
}


BOKeyManager::~BOKeyManager()
{
}

bool BOKeyManager::Initialize(std::string p_mapFileName)
{
	m_keys = std::vector<BOObject>();
	m_keysNeeded = 1;
	m_keysCatched = 0;
	// BOHudManager::SetKeys(m_keysLeft);

	// Temp add key
	BOObject key = BOObject();
	key.Initialize(float2(600, 150), int2(80, 80), 0.5f, "Sprites/PlaceHolderPNG/placeholderHyperdrive.png");
	//m_keys.push_back(key);

	return true;
}

void BOKeyManager::Shutdown()
{
	m_keys.clear();
}

void BOKeyManager::Update(double p_deltaTime)
{
}

void BOKeyManager::Update(BOBall p_ball)
{
	for (unsigned int i = 0; i < m_keys.size(); i++)
	{
		if (BOPhysics::CollisionRadiusRadius(m_keys[i].GetPosition(), m_keys[i].GetBoundingSphere().radius, p_ball.GetPosition(), p_ball.GetBoundingSphere().radius))
		{
			m_keys[i].Shutdown();
			m_keys.erase(m_keys.begin() + i);
			i--;
			KeyCatched();
		}
	}
}

void BOKeyManager::Draw()
{
	// Draw the keys
	for (unsigned int i = 0; i < m_keys.size(); i++)
	{
		m_keys[i].Draw();
	}
}

void BOKeyManager::KeyCatched()
{
	if (m_keysNeeded - m_keysCatched > 0)
	{
		m_keysCatched++;
	}
	// BOHudManager::SetKeys(m_keysLeft);
}

bool BOKeyManager::AllKeysCatched()
{
	return (m_keysNeeded - m_keysCatched) == 0;
}

bool BOKeyManager::LoadKeysFromMap(std::string p_filename)
{
	bool result = false;
	BOMapLoader mapLoader = BOMapLoader();
	result = mapLoader.Initialize();
	if (!result)
	{
		return false;
	}
	mapLoader.LoadMap(p_filename);
	std::vector<Block> blockDescriptions = mapLoader.GetLoadedBlocks();

	for (unsigned int i = 0; i < blockDescriptions.size(); i++)
	{
		switch (blockDescriptions[i].m_type)
		{
			// case KEY:
			// add a new key to the vector
		}
	}

	return true;
}