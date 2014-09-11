#include "BOPhysics.h"

const double BOPhysics::PI = 3.14159265359;
const double BOPhysics::HALF_PI = PI / 2;

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
	float2 point1, point2;
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointUpLeft, p_hexagon.pointUpRight, point1, point2);
	if (point1.x >= p_hexagon.pointUpLeft.x && point1.x <= p_hexagon.pointUpRight.x && point1.y == p_hexagon.pointUpLeft.y && point1.y == p_hexagon.pointUpRight.y && point2.x == -1000)
	{
		return true;
	}
	else if ((point1.x >= p_hexagon.pointUpLeft.x && point1.x <= p_hexagon.pointUpRight.x && point1.y == p_hexagon.pointUpLeft.y && point1.y == p_hexagon.pointUpRight.y) 
		|| (point2.x >= p_hexagon.pointUpLeft.x && point2.x <= p_hexagon.pointUpRight.x && point2.y == p_hexagon.pointUpLeft.y && point2.y == p_hexagon.pointUpRight.y))
	{
		return true;
	}
	
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointUpRight, p_hexagon.pointRight, point1, point2);
	if (point1.x >= p_hexagon.pointUpRight.x && point1.x <= p_hexagon.pointRight.x && point1.y >= p_hexagon.pointUpRight.y && point1.y <= p_hexagon.pointRight.y && point2.x == -1000)
	{
		return true;
	}
	else if ((point1.x >= p_hexagon.pointUpRight.x && point1.x <= p_hexagon.pointRight.x && point1.y >= p_hexagon.pointUpRight.y && point1.y <= p_hexagon.pointRight.y)
		|| (point2.x >= p_hexagon.pointUpRight.x && point2.x <= p_hexagon.pointRight.x && point2.y >= p_hexagon.pointUpRight.y && point2.y <= p_hexagon.pointRight.y))
	{
		return true;
	}
	
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointRight, p_hexagon.pointDownRight, point1, point2);
	if (point1.x <= p_hexagon.pointRight.x && point1.x >= p_hexagon.pointDownRight.x && point1.y >= p_hexagon.pointRight.y && point1.y <= p_hexagon.pointDownRight.y && point2.x == -1000)
	{
		return true;
	}
	else if ((point1.x <= p_hexagon.pointRight.x && point1.x >= p_hexagon.pointDownRight.x && point1.y >= p_hexagon.pointRight.y && point1.y <= p_hexagon.pointDownRight.y)
		|| (point2.x <= p_hexagon.pointRight.x && point2.x >= p_hexagon.pointDownRight.x && point2.y >= p_hexagon.pointRight.y && point2.y <= p_hexagon.pointDownRight.y))
	{
		return true;
	}
	
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointDownRight, p_hexagon.pointDownLeft, point1, point2);
	if (point1.x <= p_hexagon.pointDownRight.x && point1.x >= p_hexagon.pointDownLeft.x && point1.y >= p_hexagon.pointDownRight.y && point1.y <= p_hexagon.pointDownLeft.y && point2.x == -1000)
	{
		return true;
	}
	else if ((point1.x <= p_hexagon.pointDownRight.x && point1.x >= p_hexagon.pointDownLeft.x && point1.y >= p_hexagon.pointDownRight.y && point1.y <= p_hexagon.pointDownLeft.y)
		|| (point2.x <= p_hexagon.pointDownRight.x && point2.x >= p_hexagon.pointDownLeft.x && point2.y >= p_hexagon.pointDownRight.y && point2.y <= p_hexagon.pointDownLeft.y))
	{
		return true;
	}
	
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointDownLeft, p_hexagon.pointLeft, point1, point2);
	if (point1.x <= p_hexagon.pointDownLeft.x && point1.x >= p_hexagon.pointLeft.x && point1.y <= p_hexagon.pointDownLeft.y && point1.y >= p_hexagon.pointLeft.y && point2.x == -1000)
	{
		return true;
	}
	else if ((point1.x <= p_hexagon.pointDownLeft.x && point1.x >= p_hexagon.pointLeft.x && point1.y <= p_hexagon.pointDownLeft.y && point1.y >= p_hexagon.pointLeft.y)
		|| (point2.x <= p_hexagon.pointDownLeft.x && point2.x >= p_hexagon.pointLeft.x && point2.y <= p_hexagon.pointDownLeft.y && point2.y >= p_hexagon.pointLeft.y))
	{
		return true;
	}

	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointLeft, p_hexagon.pointUpLeft, point1, point2);
	if (point1.x >= p_hexagon.pointLeft.x && point1.x <= p_hexagon.pointUpLeft.x && point1.y <= p_hexagon.pointLeft.y && point1.y >= p_hexagon.pointUpLeft.y && point2.x == -1000)
	{
		return true;
	}
	else if ((point1.x >= p_hexagon.pointLeft.x && point1.x <= p_hexagon.pointUpLeft.x && point1.y <= p_hexagon.pointLeft.y && point1.y >= p_hexagon.pointUpLeft.y)
		|| (point2.x >= p_hexagon.pointLeft.x && point2.x <= p_hexagon.pointUpLeft.x && point2.y <= p_hexagon.pointLeft.y && point2.y >= p_hexagon.pointUpLeft.y))
	{
		return true;
	}

	if (point1.x = -1000)
	{
		return false;
	}
	
	return false;
}

void BOPhysics::CheckCollisionSphereToLine(sphere p_sphere, float2 p_point1, float2 p_point2, float2& p_returnValue1, float2& p_returnValue2)
{
	float2 localPoint1, localPoint2, point2MinusPoint1;
	localPoint1 = p_point1 - p_sphere.pos;
	localPoint2 = p_point2 - p_sphere.pos;
	float a, b, c, delta, u1, u2, squareRootDelta;

	point2MinusPoint1 = localPoint2 - localPoint1;

	a = (point2MinusPoint1.x) * (point2MinusPoint1.x) + (point2MinusPoint1.y) * (point2MinusPoint1.y);
	b = 2 * ((point2MinusPoint1.x * localPoint1.x) + (point2MinusPoint1.y * localPoint1.y));
	c = (localPoint1.x * localPoint1.x) + (localPoint1.y * localPoint1.y) - (p_sphere.radius * p_sphere.radius);
	delta = b * b - (4 * a * c);
	if (delta < 0)	// No intersection
	{
		p_returnValue1 = float2(-1000, -1000);
		p_returnValue2 = float2(-1000, -1000);
	}
	else if (delta == 0) // One intersection
	{
		// Code for returning intersecting point
		u1 = -b / (2 * a);
		p_returnValue1 = p_point1 + (point2MinusPoint1 * u1);
		p_returnValue2 = float2(-1000, -1000);
	}
	else if (delta > 0) // Two intersections
	{
		// Code for returning the two points intersecting
		squareRootDelta = sqrt(delta);

		u1 = (-b + squareRootDelta) / (2 * a);
		u2 = (-b - squareRootDelta) / (2 * a);

		p_returnValue1 = p_point1 + (point2MinusPoint1 * u1);
		p_returnValue2 = p_point1 + (point2MinusPoint1 * u2);
	}
}

int BOPhysics::CheckCollisioPadSphere(float2 p_centerPad, float p_radiusPad, double p_padRotation, float2 p_centerBall, float p_radiusBall)
{
	if (CollisionRadiusRadius(p_centerPad, p_radiusPad, p_centerBall, p_radiusBall))
	{
		//if (CheckBallInPadAngle(p_centerPad, p_radiusPad, p_PadRotation, p_centerBall, p_radiusBall))
		//{
			if		((p_centerBall.x <= (p_centerPad.x + 80.0f)) && (p_centerBall.x >= (p_centerPad.x - 80.0f)) && (p_centerBall.y <= p_centerPad.y))
			{
				return 1;
			}
			else if ((p_centerBall.x <= (p_centerPad.x + 80.0f)) && (p_centerBall.x >= (p_centerPad.x - 80.0f)) && (p_centerBall.y >= p_centerPad.y))
			{
				return 2;
			}
			else if ((p_centerBall.y <= (p_centerPad.y + 80.0f)) && (p_centerBall.y >= (p_centerPad.y - 80.0f)) && (p_centerBall.x <= p_centerPad.x))
			{
				return 3;
			}
			else
			{
				return 4;
			}
		//}
	}
	return 0;
}

bool BOPhysics::CheckBallInPadAngle(float2 p_centerPad, float p_radiusPad, double p_padRotation, float2 p_centerBall, float p_radiusBall)
{
	return true;
}

bool BOPhysics::MattiasBallPadCollision(sphere p_sphere, float2 p_sphereDir, sphere p_padSphere, double p_startAngle, double p_padSpread)
{
	if (CheckCollisionSpheres(p_sphere, p_padSphere))
	{
		float2 up = float2(0, 1);
		double alpha = acos(up.x);


		double degreesToRadians = (2 * PI) / 360;
		double rToDegrees = 360 / (2 * PI);
		double startAngle = p_startAngle;
		double padSpread = p_padSpread;
		startAngle *= degreesToRadians;
		padSpread *= degreesToRadians;


		double startAngleMA = HALF_PI - startAngle;


		float2 centerToSphere = (p_sphere.pos - p_padSphere.pos).normalized();
		centerToSphere.y *= -1;

		double arccos = acos(centerToSphere.x);
		double arcsin = asin(centerToSphere.y);

		float ctpAngle = acos(centerToSphere.x);
		//ctpAngle -= HALF_PI;
		if (centerToSphere.x < 0 && centerToSphere.y < 0)
		{
			ctpAngle *= -1;
		}

		if (centerToSphere.x < 0 && centerToSphere.y > 0)
		{
			// Rätt?
		}

		if (centerToSphere.x > 0 && centerToSphere.y < 0)
		{
			ctpAngle *= -1;
		}

		if (centerToSphere.x > 0 && centerToSphere.y > 0)
		{
			// Rätt?
		}
	
		if (ctpAngle < 0.0f)
		{
			ctpAngle += 2 * PI;
		}

		if (startAngleMA < 0.0f)
		{
			startAngleMA += 2 * PI;
		}

		if ((ctpAngle < startAngleMA) && (ctpAngle > (startAngleMA - padSpread)))
		{
			//std::cout << "Hit!";
			return true;
		}

		if ((startAngleMA - padSpread) < 0)
		{
			double padAngle = startAngleMA - padSpread + (2 * PI);
			if (((ctpAngle > 0) && (ctpAngle < startAngleMA)) || ((ctpAngle > padAngle < (2 * PI))))
			{
				//std::cout << "Hit!";
				return true;
			}
		}

		return false;
	
		/*
		if (ctpAngle < 0)
		{
			ctpAngle += 2 * PI;
		}
		*/

		if (ctpAngle < 0.0f)
		{
			ctpAngle += 2 * PI;
		}

		if (startAngle < 0.0f)
		{
			startAngle += PI * 2;
		}

		//std::cout << "Start Angle: " << startAngle * rToDegrees << "End Angle: " << rToDegrees * (startAngle + padSpread) << "CTP Angle: " << rToDegrees * ctpAngle << std::endl;

		if (ctpAngle > startAngle && ctpAngle < startAngle + padSpread)
		{
			return true;
		}
		float overlap = -((2 * PI) - (startAngle + padSpread));
		if ((overlap > 0) && (ctpAngle < overlap))
		{
			return true;
		}

		
	}
	return false;
	//if (CheckCollisionSpheres(p_sphere, p_padSphere))
	//{
	float2 big, small;
	big = float2(0.0f, 0.0f);

	small = float2(1.0f, 1.0f);
	float2 smallDir = float2(-0.5f, -0.5f);

	float2 smallToBig = big - small; // should be -1, -1

	float x = 1.0f;
	float y = 0.001f;


	// ??????????
	double test = cos(1.58);
	double test2 = acos(test); // <-- Should be 1.9
	// ?????????????????



	float2 exampleVector = float2(-1, -1);
	float2 normalizedExampleVector = exampleVector.normalized();
	float angle = acos(normalizedExampleVector.x);
	if (exampleVector.y < 0)
	{
		angle += HALF_PI;
	}
	float anglePlusHalf = angle + 1.57;

	float normalizedAngleA = acos(normalizedExampleVector.x);
	float normalizedAngleB = asin(test);

	return true;
	//}

	return 0;
}