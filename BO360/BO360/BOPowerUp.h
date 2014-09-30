#ifndef BOPOWERUP_H_
#define BOPOWERUP_H_

#include "BOObject.h"
#include "BOPowerUpManager.h"

class BOPoweUpManager;
class BOPowerUp : public BOObject
{
public:
	BOPowerUp();
	~BOPowerUp();

	bool Initialize(PowerUpTypes p_type, float2 p_position, int2 p_size, std::string p_fileName, float p_speed, int2 p_windowSize);
	void Shutdown();

	virtual void Update(double p_deltaTime);
	void Draw();
	virtual void Activate();
	virtual void Deactivate();
	virtual bool GetActive();
	virtual void SetActive(bool p_isActive);
	virtual float2 GetDirection();
	PowerUpTypes GetType();

protected:
	bool m_hasSpawned;
	float m_speed;
	int2 m_windowSize;
	float2 m_direction;
	bool m_isActive;
	bool m_hasActivated;
	PowerUpTypes m_type;
};

#endif