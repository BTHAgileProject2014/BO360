#include "BOBlock.h"


BOBlock::BOBlock()
{
	dead = false;
}


BOBlock::~BOBlock()
{
}

bool BOBlock::Initialize(float2 p_position, int2 p_size, std::string p_fileName, PowerUpTypes p_powerup)
{
	if (!BOObject::Initialize(p_position, p_size, p_fileName))
	{
		return false;
	}

	m_powerup = p_powerup;

	return true;
}
void BOBlock::Update()
{

}

box BOBlock::GetBoundingBox()
{
	return box(m_position, m_size);
}

hexagon BOBlock::GetBoundingHexagon()
{
	return hexagon(m_position, m_size);
}

void BOBlock::SetDead()
{
	dead = true;
}

bool BOBlock::GetDead()
{
	return dead;
}

PowerUpTypes BOBlock::GetPowerUp()
{
	return m_powerup;
}