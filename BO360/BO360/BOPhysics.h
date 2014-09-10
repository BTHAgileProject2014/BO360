#ifndef BOPHYSICS_H_
#define BOPHYSICS_H_

#include "BOUtility.h"
#include <math.h>

class BOPhysics
{
public:
	static bool CollisionRadiusRadius(float2 p_centerA, float p_radiusA, float2 p_centerB, float p_radiusB);
};
#endif