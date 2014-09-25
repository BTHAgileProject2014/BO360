#pragma once
#include "BOBlock.h"
class BOBlockIron :
	public BOBlock
{
public:
	BOBlockIron();
	~BOBlockIron();
	bool Hit(int p_damage);
};

