#include "BOKeyManager.h"


BOKeyManager::BOKeyManager()
{
}


BOKeyManager::~BOKeyManager()
{
}

bool BOKeyManager::Initialize()
{
	m_keysLeft = 1;
	// BOHudManager::SetKeys(m_keysLeft);

	return true;
}

void BOKeyManager::Shutdown()
{
}

void BOKeyManager::Update(double p_deltaTime)
{
	// Call the hud manager to update how many keys we have?
	// BOHudManager::SetKeys(m_keysLeft);
}

void BOKeyManager::Draw()
{
}

int BOKeyManager::GetKeysLeft()
{
	return m_keysLeft;
}

bool BOKeyManager::Won()
{
	return m_keysLeft == 0;
}