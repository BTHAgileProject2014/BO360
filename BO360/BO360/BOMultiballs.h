#ifndef BOMULTIBALLS_H_
#define BOMULTIBALLS_H_

#include "BOObject.h"
#include "BOPowerUp.h"
#include "BOPowerUpManager.h"

class BOMultiballs : public BOPowerUp
{
public:
	BOMultiballs();
	~BOMultiballs();

	void SwitchActive();

	bool Initialize(float2 p_position, int2 p_size, std::string p_fileName, float p_speed, int2 p_windowSize);
	void Activate();
	void Deactivate();

private:
	bool m_isActive;
};
#endif // !BOMULTIBALLS_H_
