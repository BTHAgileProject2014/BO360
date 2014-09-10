#pragma once
#include "BOObject.h"
#ifndef BOBLACKHOLE_H_
#define BOBLACKHOLE_H_

class BOBlackHole :
	public BOObject
{
public:
	BOBlackHole();
	~BOBlackHole();

	void Update();
};

#endif