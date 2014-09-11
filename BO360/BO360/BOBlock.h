#ifndef BOBLOCK_H_
#define BOBLOCK_H_

#include "BOObject.h"

class BOBlock :
	public BOObject
{
public:
	BOBlock();
	~BOBlock();
	void Update();
	box GetBoundingBox();
	hexagon GetBoundHexagon();
};

#endif