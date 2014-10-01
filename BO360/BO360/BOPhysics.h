#ifndef BOPHYSICS_H_
#define BOPHYSICS_H_

#include "BOUtility.h"
#include <math.h>
#include <iostream>
#include <string>

inline void NormalizeAngle(float& angle) {
	while (angle < 0) { angle += 6.2831852; }
	while (angle > 6.2831852) { angle -= 6.2831852; }
}
inline void NormalizeAngle(double& angle) {
	while (angle < 0) { angle += 6.283185307179586; }
	while (angle > 6.283185307179586) { angle -= 6.283185307179586; }
}

class BOPhysics
{
public:
	static bool CollisionRadiusRadius(float2 p_centerA, float p_radiusA, float2 p_centerB, float p_radiusB);
	static bool CheckCollisionBoxToBox(box p_box1, box p_box2);//
	static bool CheckCollisionPointToBox(int2 p_point, box p_box);//
	static bool CheckCollisionSphereToHexagon(sphere p_sphere, hexagon p_hexagon, float2& normal);//
	static void CheckCollisionSphereToLine(sphere p_sphere, float2 point1, float2 point2, float2& p_returnValue1, float2& p_returnValue2);//
	static float2 ReflectBallAroundNormal(float2 p_ballDir,float2 p_normal);//
	static float2 BlackHoleGravity(sphere p_ball, float2 p_ballDirection, float p_ballSpeed, sphere p_blackHole, double p_deltaTime);//
	static float2 BallPadCollision(sphere p_sphere, float2 p_sphereDir, sphere p_padSphere, double p_startAngle, double p_endAngle);//
	static float CalculateBallFuel(float p_fuel, double p_deltaTime);//

	static int CheckCollisionBallShield(sphere p_sphere, sphere p_padSphere);//

private:
	static float2 CalculateNewDir(float2 currentDir, float p_padAngle, float p_maxWidthAngle, float p_ballAngle);//
	static float CalculateDistance(float2 p_Ball, float2 p_BlackHole);//


	static const double PI;
	static const double HALF_PI;


};
#endif
