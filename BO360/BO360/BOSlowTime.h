#ifndef BOSLOWTIME_H_
#define BOSLOWTIME_H_
#include "BOComponent.h"
#include "BOPhysics.h"

class BOSlowTime: public BOComponent
{
public:
    BOSlowTime();
    ~BOSlowTime();

    bool Initialize();
    void Shutdown();

    void Update(double p_deltaTime);
    void Activate();
    void AddCharges(int p_charges);

private:
    int m_charges;
    float m_maxTime;
    bool m_active;
    float m_timeLeft;
    int m_fade;
    float m_minTimeScale;
    float m_currentTimeScale;
    float m_fadeTime;
};
#endif
