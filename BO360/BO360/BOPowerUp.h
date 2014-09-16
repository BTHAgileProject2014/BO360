#ifndef BOPOWERUP_H_
#define BOPOWERUP_H_

#include "BOObject.h"

class BOPowerUp : BOObject
{
public:
	BOPowerUp();
	~BOPowerUp();

	bool Initialize(float2 p_position, int2 p_size, std::string p_fileName);
	void Shutdown();
	void Draw();

	virtual void Update();
};

#endif