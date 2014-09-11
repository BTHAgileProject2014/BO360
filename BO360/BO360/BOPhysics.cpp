#include "BOPhysics.h"

bool BOPhysics::CollisionRadiusRadius(float2 p_centerA, float p_radiusA, float2 p_centerB, float p_radiusB)
{
	// Calculate x and y distance.
	float distanceX = p_centerA.x - p_centerB.x;
	float distanceY = p_centerA.y - p_centerB.y;

	// Calculate the distance as a single value.
	float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

	// If the distance are equal or less than the sum of the two radii, the circles collide.
	return (distance <= (p_radiusA + p_radiusB));
}

bool BOPhysics::CheckCollisionSpheres(sphere p_sphere1, sphere p_sphere2)
{
	float2 distance = float2(p_sphere1.pos.x - p_sphere2.pos.x, p_sphere1.pos.y - p_sphere2.pos.y);
	float length = distance.length();

	if (length <= p_sphere1.radius + p_sphere2.radius)
	{
		//They have collided
		return true;
	}
	
	return false;
}
int BOPhysics::CheckCollisioPadSphere(float2 p_centerPad, float p_radiusPad, double p_padRotation, float2 p_centerBall, float p_radiusBall)
{
	if (CollisionRadiusRadius(p_centerPad, p_radiusPad, p_centerBall, p_radiusBall))
	{
		//if (CheckBallInPadAngle(p_centerPad, p_radiusPad, p_PadRotation, p_centerBall, p_radiusBall))
		//{

		//}

		if		((p_centerBall.x < (p_centerPad.x + 80.0f)) && (p_centerBall.x > (p_centerPad.x - 80.0f)) && (p_centerBall.y < p_centerPad.y))
		{
			return 1;
		}
		else if ((p_centerBall.x < (p_centerPad.x + 80.0f)) && (p_centerBall.x > (p_centerPad.x - 80.0f)) && (p_centerBall.y > p_centerPad.y))
		{
			return 2;
		}
		else if ((p_centerBall.y < (p_centerPad.y + 80.0f)) && (p_centerBall.y >(p_centerPad.y - 80.0f)) && (p_centerBall.x < p_centerPad.x))
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}
	return 0;
}
bool BOPhysics::CheckBallInPadAngle(float2 p_centerPad, float p_radiusPad, double p_padRotation, float2 p_centerBall, float p_radiusBall)
{

	return true;
}