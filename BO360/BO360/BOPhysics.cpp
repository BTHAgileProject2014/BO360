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