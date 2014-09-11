#include "BOBlock.h"


BOBlock::BOBlock()
{
	dead = false;
}


BOBlock::~BOBlock()
{
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
