#ifndef BOPHYSICS_H_
#define BOPHYSICS_H_

#include "BOUtility.h"
#include <math.h>

class BOPhysics
{
public:
	static bool CollisionRadiusRadius(float2 p_centerA, float p_radiusA, float2 p_centerB, float p_radiusB);
	static bool CheckCollisionSpheres(sphere p_sphere1, sphere p_sphere2);
	static int CheckCollisioPadSphere(float2 p_centerPad, float p_radiusPad, double p_PadRotation, float2 p_centerBall, float p_radiusBall);

private:
	static bool CheckBallInPadAngle(float2 p_centerPad, float p_radiusPad, double p_PadRotation, float2 p_centerBall, float p_radiusBall);
};
#endif