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
    m_charges = 0;
    m_timeLeft = 0;
    m_active = false;
    m_charges = 0;
    m_maxTime = 10.0f;
    m_currentTimeScale = 1.0f;
    m_minTimeScale = 0.3f;
    m_fadeTime = m_maxTime*0.2f; // 1/5 for now;
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
                if (m_timeLeft < 2.0f)
                {
                    FadeState = FadeOut;
                }
                break;
            case FadeIn:
                if (m_timeLeft < m_maxTime - 2.0f)
                {
                    m_currentTimeScale = m_minTimeScale;
                    BOPhysics::SetTimeScale(m_currentTimeScale);
                    FadeState = NotFading;
                }
                else
                {
                    m_currentTimeScale -= 0.3f * (float)p_deltaTime;
                    BOPhysics::SetTimeScale(m_currentTimeScale);
                }
                break;
            case FadeOut:
                
                if (m_timeLeft < 0)
                {
                    m_active = false;
                    m_currentTimeScale = 1.0f;
                    BOPhysics::SetTimeScale(m_currentTimeScale);
                }
                else
                {
                    m_currentTimeScale += 0.3f * (float)p_deltaTime;
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
            m_timeLeft = m_maxTime;
            m_active = true;
            FadeState = FadeIn;
        }
    }
}

void BOSlowTime::AddCharges(int p_charges)
{
    m_charges += p_charges;
}




