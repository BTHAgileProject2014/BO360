#ifndef BOPHYSICS_H_
#define BOPHYSICS_H_

#include "BOUtility.h"
#include <math.h>
#include <iostream>
#include <string>

class BOPhysics
{
public:
	static bool CollisionRadiusRadius(float2 p_centerA, float p_radiusA, float2 p_centerB, float p_radiusB);
	static bool CheckCollisionSpheres(sphere p_sphere1, sphere p_sphere2);
	static bool CheckCollisionBoxToBox(box p_box1, box p_box2);
	static bool CheckCollisionSphereToHexagon(sphere p_sphere, hexagon p_hexagon, float2& normal);
	static void CheckCollisionSphereToLine(sphere p_sphere, float2 point1, float2 point2, float2& p_returnValue1, float2& p_returnValue2);
	static int CheckCollisioPadSphere(sphere p_sphere, float2 p_sphereDir, sphere p_padSphere, double p_startAngle, double p_endAngle);
	static float2 BallPadCollision(sphere p_sphere, float2 p_sphereDir, sphere p_padSphere, double p_startAngle, double p_endAngle);
	static int CheckCollisionBallShield(sphere p_sphere, sphere p_padSphere);

private:
	static float2 CalculateNewDir(float2 currentDir, float2 padNormal, float distanceFromCenter, float maxDistanceFromCenter);
	static bool CheckBallInPadAngle(float2 p_centerPad, float p_radiusPad, double p_PadRotation, float2 p_centerBall, float p_radiusBall);
	static const double PI;
	static const double HALF_PI;
};
#endif


/*
if (p_bounceCorner == 0)
return;
m_hasColided = true;

float2 ballDir = m_ballList[0].GetDirection();
if (p_bounceCorner == 1 || p_bounceCorner == 2)//Straight up and down corner
{
ballDir.y *= (-1);
//std::cout << "Krock" << std::endl;
}
else//Straight right and left corner
{
ballDir.x *= (-1);
//std::cout << "Krock" << std::endl;
}
m_ballList[0].SetDirection(ballDir);
*/
