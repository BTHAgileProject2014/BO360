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

    m_duration = 0.0;
    m_timeLeft = 0.0;
    m_draw = false;
    m_wave = BOTextureManager::GetTexture(TEXSHOCKWAVE);

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
            BOHUDManager::SetShockwave(m_hasShockwave);
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
    BOHUDManager::SetShockwave(m_hasShockwave);
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

void BOShockwave::BeginDrawingWave(double p_duration)
{
    m_duration = p_duration;
    m_timeLeft = m_duration;

    m_draw = true;
}

void BOShockwave::UpdateWave(double p_deltaTime)
{
    m_timeLeft -= p_deltaTime * BOPhysics::GetTimeScale();

    if (m_timeLeft < 0)
    {
        m_timeLeft = 0;
        m_duration = 0;
        m_draw = false;
    }
}

void BOShockwave::DrawWave()
{
    if (m_draw)
    {
        float scale = 1.0f - (float)(m_timeLeft / m_duration);
        float size = 2000.0f * scale;

        if (size > 0)
        {
            int4 source = int4(0, 0, 1300, 1300);
            int4 target = int4((BOGraphicInterface::GetWindowSize().x / 2) - (int)size / 2, (BOGraphicInterface::GetWindowSize().y / 2) - (int)size / 2, (int)size, (int)size);

            BOGraphicInterface::DrawEx(m_wave, source, target, 0, int2(0, 0), 255);
        }
    }
}
