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

bool BOPhysics::CheckCollisionBoxToBox(box p_box1, box p_box2)
{
	if (p_box1.bottom < p_box2.top || p_box1.top > p_box2.bottom || p_box1.left > p_box2.right || p_box1.right < p_box2.left)
	{
		return false;
	}

	return true;
}

bool BOPhysics::CheckCollisionSphereToHexagon(sphere p_sphere, hexagon p_hexagon)
{
	if (CheckCollisionSphereToLine(p_sphere, p_hexagon.pointUpLeft, p_hexagon.pointUpRight))
	{
		return true;
	}
	else if (CheckCollisionSphereToLine(p_sphere, p_hexagon.pointUpRight, p_hexagon.pointRight))
	{
		return true;
	}
	else if(CheckCollisionSphereToLine(p_sphere, p_hexagon.pointRight, p_hexagon.pointDownRight))
	{
		return true;
	}
	else if (CheckCollisionSphereToLine(p_sphere, p_hexagon.pointDownRight, p_hexagon.pointDownLeft))
	{
		return true;
	}
	else if (CheckCollisionSphereToLine(p_sphere, p_hexagon.pointDownLeft, p_hexagon.pointLeft))
	{
		return true;
	}
	else if (CheckCollisionSphereToLine(p_sphere, p_hexagon.pointLeft, p_hexagon.pointUpLeft))
	{
		return true;
	}

	return false;
}

bool BOPhysics::CheckCollisionSphereToLine(sphere p_sphere, float2 p_point1, float2 p_point2)
{
	float2 localPoint1, localPoint2, point2MinusPoint1;
	localPoint1 = p_point1 - p_sphere.pos;
	localPoint2 = p_point2 - p_sphere.pos;
	float a, b, c, delta, u1, u2, squareRootDelta;

	point2MinusPoint1 = localPoint2 - localPoint1;

	a = (point2MinusPoint1.x) * (point2MinusPoint1.x) + (point2MinusPoint1.y)* (point2MinusPoint1.y);
	b = 2 * ((point2MinusPoint1.x * localPoint1.x) + (point2MinusPoint1.y * localPoint1.y));
	c = (localPoint1.x * localPoint1.x) + (localPoint1.y * localPoint1.y) - (p_sphere.radius * p_sphere.radius);
	delta = b * b - (4 * a * c);
	if (delta < 0)	// No intersection
	{
		return false;
	}
	else if (delta == 0) // One intersection
	{
		return true;
		// Code for returning intersecting point
		/*
		u1 = -b / (2 * a);
		return p_point1 + (u1 * point2MinusPoint1);
		*/
	}
	else if (delta > 0) // Two intersections
	{
		return true;
		// Code for returning the two points intersecting
		/*
		squareRootDelta = sqrt(delta);

		u1 = (-b + squareRootDelta) / (2 * a);
		u2 = (-b - squareRootDelta) / (2 * a);

		return{ p_point1 + (u1 * point2MinusPoint1); p_point1 + (u2 * point2MinusPoint1) }
		*/
	}

	return false;
}