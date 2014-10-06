#ifndef BOSHOCKWAVE_H_
#define BOSHOCKWAVE_H_

#include "BOComponent.h"
#include "BOPUSubscriber.h"
#include "BOPowerUpManager.h"
#include "BOHUDManager.h"

class BOShockwave : public BOComponent, public BOPUSubscriber
{
public:
    BOShockwave();
    ~BOShockwave();

    bool Initialize();
    void Shutdown();
    void Update(double p_deltaTime);

    bool Activate();
    void AddShockwave(bool p_isPowerUp);
    void Handle(PowerUpTypes p_type, bool p_activated);
    double GetTimeLeft() const;
private:
    bool m_hasShockwave;
    bool m_isPowerUp;
    double m_totalCooldownTime;
    double m_currentCooldownTime;
};

#endif