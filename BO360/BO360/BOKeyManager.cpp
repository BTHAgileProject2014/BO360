#include "BOKeyManager.h"

BOKeyManager::BOKeyManager()
{

}

BOKeyManager::~BOKeyManager()
{

}

bool BOKeyManager::Initialize()
{
	m_keys = std::vector<BOObject>();
	m_keysNeeded = 0;
	m_keysCatched = 0;
    BOHUDManager::SetKeys(m_keysCatched, m_keysNeeded);
	return true;
}

void BOKeyManager::Shutdown()
{
	m_keys.clear();
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

void BOKeyManager::AddKey(float2 p_position, int2 p_size, float p_scale, SDL_Texture* p_sprite)
{
    BOObject key = BOObject();
    key.Initialize(p_position, p_size, p_scale, p_sprite);
    m_keys.push_back(key);
    m_keysNeeded++;
    BOHUDManager::SetKeys(m_keysCatched, m_keysNeeded);
}

void BOKeyManager::KeyCatched()
{
	if (m_keysNeeded - m_keysCatched > 0)
	{
		m_keysCatched++;
	}
    BOHUDManager::SetKeys(m_keysCatched, m_keysNeeded);
}

bool BOKeyManager::AllKeysCatched()
{
    // If no key is added it returns false so you don't win directly
    if (m_keysNeeded == 0)
    {
        return false;
    }

	return (m_keysNeeded - m_keysCatched) == 0;
}