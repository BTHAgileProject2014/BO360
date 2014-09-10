#ifndef BOBLACKHOLE_H_
#define BOBLACKHOLE_H_

#include "BOObject.h"

class BOBlackHole : public BOObject
{
public:
	BOBlackHole();
	~BOBlackHole();

	void Update();

	sphere GetBoundingSphere();
};
#endif