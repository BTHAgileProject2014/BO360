#ifndef BOSLOWTIME_H_
#define BOSLOWTIME_H_
#include "BOComponent.h"
#include "BOPhysics.h"
#include "BOHUDManager.h"
#include "BOSoundManager.h"

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
    float m_duration;
    bool m_active;
    float m_timeLeft;
    float m_minTimeScale;
    float m_maxTimeScale;
    float m_currentTimeScale;
    float m_fadeTime;
};
#endif
