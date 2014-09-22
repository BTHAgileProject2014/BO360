#ifndef BOBLOCK_H_
#define BOBLOCK_H_

#include "BOObject.h"

class BOBlock :
	public BOObject
{
public:
	BOBlock();
	~BOBlock();
	bool Initialize(float2 p_position, int2 p_size, std::string p_fileName, PowerUpTypes p_powerup);
	void Update();
	box GetBoundingBox();
	hexagon GetBoundingHexagon();
	void SetDead();
	bool GetDead();
	PowerUpTypes GetPowerUp();

private:
	bool dead;
	PowerUpTypes m_powerup;
};

#endif