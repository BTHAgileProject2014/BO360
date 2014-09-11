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
