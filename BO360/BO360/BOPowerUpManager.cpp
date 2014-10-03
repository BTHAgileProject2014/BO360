#include "BOPowerUpManager.h"

std::vector<BOPUSubscriber*> BOPowerUpManager::m_subscribers;
std::vector<BOPowerUp*> BOPowerUpManager::m_powerUps;

BOPowerUpManager::BOPowerUpManager()
{

}

BOPowerUpManager::~BOPowerUpManager()
{

}

bool BOPowerUpManager::Initialize()
{
	m_powerUps = std::vector<BOPowerUp*>();
	m_subscribers = std::vector<BOPUSubscriber*>();	

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

void BOPowerUpManager::AddPowerUp(PowerUpTypes p_type, float2 p_startPosition, BOPaddle* p_paddle, float2 p_blackholePosition)
{
	
	switch (p_type)
	{
		case PUBiggerPad:
		{
			BOPowerUp* biggerPad = new BOPowerUp();
			biggerPad->Initialize(PUBiggerPad, p_startPosition, int2(30, 30), BOTextureManager::GetTexture(TEXPU3), 500.0f, p_paddle, p_blackholePosition);
			m_powerUps.push_back(biggerPad);
			break;
		}

		case PUSmallerPad:
		{
			break;
		}
		case PUShield:
		{
			BOPowerUp* shield = new BOPowerUp();
			shield->Initialize(PUShield, p_startPosition, int2(30, 30), BOTextureManager::GetTexture(TEXPU2), 500.0f, p_paddle, p_blackholePosition);
			m_powerUps.push_back(shield);
			break;
		}	
		case PUExtraBall:
		{
			BOPowerUp* extraBall = new BOPowerUp();
			extraBall->Initialize(PUExtraBall, p_startPosition, int2(40, 40), BOTextureManager::GetTexture(TEXPUMULTIBALL), 500.0f, p_paddle, p_blackholePosition);
			m_powerUps.push_back(extraBall);
			break;
		}
	}
}

void BOPowerUpManager::RemovePowerUp(BOPowerUp* p_powerUp)
{
	for (unsigned int i = 0; i < m_powerUps.size(); i++)
	{
		if (p_powerUp == m_powerUps[i])
		{
            delete m_powerUps[i];
			m_powerUps.erase(m_powerUps.begin() + i);
			break;
		}
	}
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