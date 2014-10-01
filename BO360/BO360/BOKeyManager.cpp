#include "BOKeyManager.h"


BOKeyManager::BOKeyManager()
{
}


BOKeyManager::~BOKeyManager()
{
}

bool BOKeyManager::Initialize()
{
	m_keys = std::vector<BOKey>();
	m_keysLeft = 1;
	// BOHudManager::SetKeys(m_keysLeft);

	return true;
}

void BOKeyManager::Shutdown()
{
	m_keys.clear();
}

void BOKeyManager::Update(double p_deltaTime)
{
	// Update the keys
	for (unsigned int i = 0; i < m_keys.size(); i++)
	{
		m_keys[i].Update(p_deltaTime);
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

int BOKeyManager::GetKeysLeft()
{
	return m_keysLeft;
}

void BOKeyManager::KeyCatched()
{
	if (m_keysLeft > 0)
	{
		m_keysLeft--;
	}
}

bool BOKeyManager::AllKeysCatched()
{
	return m_keysLeft == 0;
}