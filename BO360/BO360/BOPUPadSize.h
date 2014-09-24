#ifndef BOPUPADSIZE_H_
#define BOPUPADSIZE_H_

#include "BOObject.h"
#include "BOPowerUp.h"
#include "BOPowerUpManager.h"

class BOPUPadSize :
	public BOPowerUp
{
public:
	BOPUPadSize();
	~BOPUPadSize();

	bool Initialize(float2 p_position, int2 p_size, std::string p_fileName, float p_speed, int2 p_windowSize);
	void Activate();
	void Deactivate();
};

#endif // !BOPUPADSIZE_H_