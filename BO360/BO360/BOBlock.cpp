#include "BOBlock.h"


BOBlock::BOBlock()
{
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
