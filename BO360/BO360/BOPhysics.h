#ifndef BOPHYSICS_H_
#define BOPHYSICS_H_

#include "BOUtility.h"
#include <math.h>
#include <iostream>

class BOPhysics
{
public:
	static bool CollisionRadiusRadius(float2 p_centerA, float p_radiusA, float2 p_centerB, float p_radiusB);
	static bool CheckCollisionSpheres(sphere p_sphere1, sphere p_sphere2);
	static bool CheckCollisionBoxToBox(box p_box1, box p_box2);
	static bool CheckCollisionSphereToHexagon(sphere p_sphere, hexagon p_hexagon);
	static void CheckCollisionSphereToLine(sphere p_sphere, float2 point1, float2 point2, float2& p_returnValue1, float2& p_returnValue2);
	static int CheckCollisioPadSphere(sphere p_sphere, float2 p_sphereDir, sphere p_padSphere, double p_startAngle, double p_endAngle);
	static bool BallPadCollision(sphere p_sphere, float2 p_sphereDir, sphere p_padSphere, double p_startAngle, double p_endAngle);

private:
	static bool CheckBallInPadAngle(float2 p_centerPad, float p_radiusPad, double p_PadRotation, float2 p_centerBall, float p_radiusBall);
	static const double PI;
	static const double HALF_PI;
};
#endif