#include "BOPowerUpManager.h"
std::vector<BOPUSubscriber*> BOPowerUpManager::m_subscribers;
std::vector<BOPowerUp*> BOPowerUpManager::m_powerUps;


BOPowerUpManager::BOPowerUpManager()
{
}


BOPowerUpManager::~BOPowerUpManager()
{
}

bool BOPowerUpManager::Initialize(int p_windowsWidth, int p_windowHeight)
{
	m_powerUps = std::vector<BOPowerUp*>();
	m_subscribers = std::vector<BOPUSubscriber*>();
	m_windowSize.x = p_windowsWidth;
	m_windowSize.y = p_windowHeight;
	
	

	return true;
}

void BOPowerUpManager::Shutdown()
{
}

void BOPowerUpManager::Notify(PowerUpTypes p_type, bool p_activated)
{
	for (unsigned int i = 0; i < m_subscribers.size(); i++)
	{
		m_subscribers[i]->Handle(p_type, p_activated);
	}
}

void BOPowerUpManager::AddPowerUp(BOPowerUp* p_powerUp)
{
	m_powerUps.push_back(p_powerUp);
}

void BOPowerUpManager::RemovePowerUp(int p_remove)
{
	delete m_powerUps[p_remove];
	m_powerUps.erase(m_powerUps.begin() + p_remove);
}

void BOPowerUpManager::Update(double p_deltaTime)
{
	for (unsigned int i = 0; i < m_powerUps.size(); i++)
	{
		m_powerUps[i]->Update(p_deltaTime);
	}
}

void BOPowerUpManager::Draw()
{
	for (unsigned int i = 0; i < m_powerUps.size(); i++)
	{
		m_powerUps[i]->Draw();
	}
}

void BOPowerUpManager::AddSubscriber(BOPUSubscriber* p_subscriber)
{
	m_subscribers.push_back(p_subscriber);
}

void BOPowerUpManager::Unsubscribe(BOPUSubscriber* p_subscriber)
{
	for (unsigned int i = 0; i < m_subscribers.size(); i++)
	{
		if (m_subscribers[i] == p_subscriber)
		{
			m_subscribers.erase(m_subscribers.begin() + i);
			break;
		}
	}
}

int BOPowerUpManager::GetPowerUpSize()
{
	return m_powerUps.size();
}

BOPowerUp* BOPowerUpManager::GetPowerUp(int p_nr)
{
	return m_powerUps[p_nr];
}