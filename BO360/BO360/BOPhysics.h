#ifndef BOPHYSICS_H_
#define BOPHYSICS_H_

#include "BOUtility.h"
#include <math.h>

class BOPhysics
{
public:
	static bool CollisionRadiusRadius(float2 p_centerA, float p_radiusA, float2 p_centerB, float p_radiusB);
	static bool CheckCollisionSpheres(sphere p_sphere1, sphere p_sphere2);
	static bool CheckCollisionBoxToBox(box p_box1, box p_box2);
	static bool CheckCollisionSphereToHexagon(sphere p_sphere, hexagon p_hexagon);
};
#endif