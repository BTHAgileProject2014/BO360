#include "BOShockwave.h"


BOShockwave::BOShockwave()
{
}


BOShockwave::~BOShockwave()
{
}

bool BOShockwave::Initialize()
{
    m_hasShockwave = false;
    m_isPowerUp = true;
    m_totalCooldownTime = 10;
    m_currentCooldownTime = 0;
    BOPowerUpManager::AddSubscriber(this);
    

    return true;
}

void BOShockwave::Shutdown()
{
    BOPowerUpManager::Unsubscribe(this);
}

void BOShockwave::Update(double p_deltaTime)
{
    // If the we have a shockwave and it is a tech tree the cooldown is increased
    if (m_hasShockwave && !m_isPowerUp && m_currentCooldownTime < m_totalCooldownTime)
    {
        m_currentCooldownTime += p_deltaTime;
    }

    // BOHudManager::SetShockwaveCD(GetTimeLeft());
}

bool BOShockwave::Activate()
{
    if (m_hasShockwave)
    {
        if (m_isPowerUp)
        {
            m_hasShockwave = false;
            return true;
        }
        else if(m_currentCooldownTime >= m_totalCooldownTime)
        {
            return true;
        }        
    }
    return false;
}

void BOShockwave::AddShockwave(bool p_isPowerUp)
{
    m_hasShockwave = true;
    if (m_isPowerUp)
    {
        m_isPowerUp = p_isPowerUp;
    }
    else
    {
        m_currentCooldownTime = m_totalCooldownTime;
    }
}

void BOShockwave::Handle(PowerUpTypes p_type, bool p_activated)
{
    if (p_type == PUShockwave && p_activated)
    {
        AddShockwave(true);
    }
}

double BOShockwave::GetTimeLeft() const
{
    if (m_currentCooldownTime < m_totalCooldownTime)
    {
        return m_totalCooldownTime - m_currentCooldownTime;
    }
    else
    {
        return 0;
    }
}