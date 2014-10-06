#include "BOSlowTime.h"

enum FadeState
{
    NotFading,
    FadeIn,
    FadeOut
}FadeState;

BOSlowTime::BOSlowTime()
{
}


BOSlowTime::~BOSlowTime()
{
}

bool BOSlowTime::Initialize()
{
    m_charges = 0; // use -1 for unlimited nr of charges
    m_timeLeft = 0;
    m_active = false;
    m_duration = 5.0f; // includes fade time, 5-(5*0.2*2) is the actual time at the min time scale
    m_minTimeScale = 0.1f;
    m_maxTimeScale = 1.0f;
    m_currentTimeScale = 1.0f;
    m_fadeTime = m_duration*0.10f;
    return true;
}

void BOSlowTime::Shutdown()
{

}

void BOSlowTime::Update(double p_deltaTime)
{
    if (m_active)
    {
        m_timeLeft -= (float)p_deltaTime;
        switch (FadeState)
        {
            case NotFading:
                if (m_timeLeft < m_fadeTime)
                {
                    FadeState = FadeOut;
                }
                break;
            case FadeIn:
                // Fade in finished
                if (m_timeLeft < m_duration - m_fadeTime)
                {
                    m_currentTimeScale = m_minTimeScale;
                    BOPhysics::SetTimeScale(m_currentTimeScale);
                    FadeState = NotFading;
                }
                else
                {
                    m_currentTimeScale -= (m_maxTimeScale-m_minTimeScale) / m_fadeTime * (float)p_deltaTime;
                    BOPhysics::SetTimeScale(m_currentTimeScale);
                }
                break;
            case FadeOut:
                // Fade out finished
                if (m_timeLeft < 0)
                {
                    m_active = false;
                    m_currentTimeScale = m_maxTimeScale;
                    BOPhysics::SetTimeScale(m_currentTimeScale);
                }
                else
                {
                    m_currentTimeScale += (m_maxTimeScale-m_minTimeScale) / m_fadeTime * (float)p_deltaTime;
                    BOPhysics::SetTimeScale(m_currentTimeScale);
                }
                break;
        }
    }
}

void BOSlowTime::Activate()
{
    if (!m_active)
    {
        if (m_charges > 0)
        {
            m_charges--;
            m_timeLeft = m_duration;
            m_active = true;
            FadeState = FadeIn;
        }
        // If you want unlimited nr of charges, use m_charges = -1; in initialize
        else if (m_charges < 0)
        {
            m_timeLeft = m_duration;
            m_active = true;
            FadeState = FadeIn;
        }
    }
}

void BOSlowTime::AddCharges(int p_charges)
{
    m_charges += p_charges;
}




