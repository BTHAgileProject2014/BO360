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
	bool Initialize(float2 p_position, int2 p_size, std::string p_fileName, int p_hp, PowerUpTypes p_powerup);
	void Update();
	box GetBoundingBox();
	hexagon GetBoundingHexagon();
	void SetDead();
	bool GetDead();
	virtual bool Hit(int p_damage); // Returns true if dead
	PowerUpTypes GetPowerUp();

protected:
	int m_hp;
	bool dead;
	PowerUpTypes m_powerup;
};

#endif