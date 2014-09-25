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

bool BOPhysics::CheckCollisionPointToBox(int2 p_point, box p_box)
{
	if (p_point.x > p_box.pos.x && p_point.x < (p_box.pos.x + p_box.size.x) && p_point.y > p_box.pos.y && p_point.y < (p_box.pos.y + p_box.size.y))
	{
		return true;
	}

	return false;
}

bool BOPhysics::CheckCollisionSphereToHexagon(sphere p_sphere, hexagon p_hexagon, float2& normal)
{
	// Create 2 points for checking collision point on line
	float2 point1, point2;

	// Check collision with the sphere and each line in the hexagon
	// Same code 6 times with differents points from the hexagon
	//					   __	
	//				      /  \
	//					  \__/
	// Upper Line _.
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointUpLeft, p_hexagon.pointUpRight, point1, point2);
	// Checking if collision in one point
	if (point1.x >= p_hexagon.pointUpLeft.x && point1.x <= p_hexagon.pointUpRight.x && point1.y == p_hexagon.pointUpLeft.y && point1.y == p_hexagon.pointUpRight.y && point2.x == -1000)
	{
		normal = float2(p_hexagon.pointUpRight.y - p_hexagon.pointUpRight.y, -1 * (p_hexagon.pointUpRight.x - p_hexagon.pointUpLeft.x));
		normal = normal.normalized();
		normal.y *= -1;
		return true;
	}
	// Checking if the ball collision with the line in two points
	else if ((point1.x >= p_hexagon.pointUpLeft.x && point1.x <= p_hexagon.pointUpRight.x && point1.y == p_hexagon.pointUpLeft.y && point1.y == p_hexagon.pointUpRight.y) 
		|| (point2.x >= p_hexagon.pointUpLeft.x && point2.x <= p_hexagon.pointUpRight.x && point2.y == p_hexagon.pointUpLeft.y && point2.y == p_hexagon.pointUpRight.y))
	{
		normal = float2(p_hexagon.pointUpRight.y - p_hexagon.pointUpRight.y,-1*( p_hexagon.pointUpRight.x - p_hexagon.pointUpLeft.x));
		normal = normal.normalized();
		//normal.y *= -1;
		return true;
	}
	
	// Upper right line \.
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointUpRight, p_hexagon.pointRight, point1, point2);
	// Checking if collision in one point
	if (point1.x >= p_hexagon.pointUpRight.x && point1.x <= p_hexagon.pointRight.x && point1.y >= p_hexagon.pointUpRight.y && point1.y <= p_hexagon.pointRight.y && point2.x == -1000)
	{
		normal = float2(p_hexagon.pointRight.y - p_hexagon.pointUpRight.y, -1 * (p_hexagon.pointRight.x - p_hexagon.pointUpRight.x));
		normal = normal.normalized();
		return true;
	}
	// Checking if the ball collision with the line in two points
	else if ((point1.x >= p_hexagon.pointUpRight.x && point1.x <= p_hexagon.pointRight.x && point1.y >= p_hexagon.pointUpRight.y && point1.y <= p_hexagon.pointRight.y)
		|| (point2.x >= p_hexagon.pointUpRight.x && point2.x <= p_hexagon.pointRight.x && point2.y >= p_hexagon.pointUpRight.y && point2.y <= p_hexagon.pointRight.y))
	{
		normal = float2(p_hexagon.pointRight.y - p_hexagon.pointUpRight.y, -1 * (p_hexagon.pointRight.x - p_hexagon.pointUpRight.x));
		normal = normal.normalized();
		return true;
	}
	
	// Lower right line /.
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointRight, p_hexagon.pointDownRight, point1, point2);
	// Checking if collision in one point
	if (point1.x <= p_hexagon.pointRight.x && point1.x >= p_hexagon.pointDownRight.x && point1.y >= p_hexagon.pointRight.y && point1.y <= p_hexagon.pointDownRight.y && point2.x == -1000)
	{
		normal = float2(p_hexagon.pointDownRight.y - p_hexagon.pointRight.y, -1 * (p_hexagon.pointDownRight.x - p_hexagon.pointRight.x));
		normal = normal.normalized();
		return true;
	}
	// Checking if the ball collision with the line in two points
	else if ((point1.x <= p_hexagon.pointRight.x && point1.x >= p_hexagon.pointDownRight.x && point1.y >= p_hexagon.pointRight.y && point1.y <= p_hexagon.pointDownRight.y)
		|| (point2.x <= p_hexagon.pointRight.x && point2.x >= p_hexagon.pointDownRight.x && point2.y >= p_hexagon.pointRight.y && point2.y <= p_hexagon.pointDownRight.y))
	{
		normal = float2(p_hexagon.pointDownRight.y - p_hexagon.pointRight.y, -1 * (p_hexagon.pointDownRight.x - p_hexagon.pointRight.x));
		normal = normal.normalized();
		return true;
	}
	
	// Lower middle line _.
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointDownRight, p_hexagon.pointDownLeft, point1, point2);
	// Checking if collision in one point
	if (point1.x <= p_hexagon.pointDownRight.x && point1.x >= p_hexagon.pointDownLeft.x && point1.y >= p_hexagon.pointDownRight.y && point1.y <= p_hexagon.pointDownLeft.y && point2.x == -1000)
	{
		normal = float2(p_hexagon.pointDownLeft.y - p_hexagon.pointDownRight.y, -1 * (p_hexagon.pointDownLeft.x - p_hexagon.pointDownRight.x));
		normal = normal.normalized();
		return true;
	}
	// Checking if the ball collision with the line in two points
	else if ((point1.x <= p_hexagon.pointDownRight.x && point1.x >= p_hexagon.pointDownLeft.x && point1.y >= p_hexagon.pointDownRight.y && point1.y <= p_hexagon.pointDownLeft.y)
		|| (point2.x <= p_hexagon.pointDownRight.x && point2.x >= p_hexagon.pointDownLeft.x && point2.y >= p_hexagon.pointDownRight.y && point2.y <= p_hexagon.pointDownLeft.y))
	{
		normal = float2(p_hexagon.pointDownLeft.y - p_hexagon.pointDownRight.y, -1 * (p_hexagon.pointDownLeft.x - p_hexagon.pointDownRight.x));
		normal = normal.normalized();
		return true;
	}
	
	// Lower Left line \.
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointDownLeft, p_hexagon.pointLeft, point1, point2);
	// Checking if collision in one point
	if (point1.x <= p_hexagon.pointDownLeft.x && point1.x >= p_hexagon.pointLeft.x && point1.y <= p_hexagon.pointDownLeft.y && point1.y >= p_hexagon.pointLeft.y && point2.x == -1000)
	{
		normal = float2(p_hexagon.pointLeft.y - p_hexagon.pointDownLeft.y, -1 * (p_hexagon.pointLeft.x - p_hexagon.pointDownLeft.x));
		normal = normal.normalized();
		return true;
	}
	// Checking if the ball collision with the line in two points
	else if ((point1.x <= p_hexagon.pointDownLeft.x && point1.x >= p_hexagon.pointLeft.x && point1.y <= p_hexagon.pointDownLeft.y && point1.y >= p_hexagon.pointLeft.y)
		|| (point2.x <= p_hexagon.pointDownLeft.x && point2.x >= p_hexagon.pointLeft.x && point2.y <= p_hexagon.pointDownLeft.y && point2.y >= p_hexagon.pointLeft.y))
	{
		normal = float2(p_hexagon.pointLeft.y - p_hexagon.pointDownLeft.y, -1 * (p_hexagon.pointLeft.x - p_hexagon.pointDownLeft.x));
		normal = normal.normalized();
		return true;
	}

	// Upper left line /.
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointLeft, p_hexagon.pointUpLeft, point1, point2);
	// Checking if collision in one point
	if (point1.x >= p_hexagon.pointLeft.x && point1.x <= p_hexagon.pointUpLeft.x && point1.y <= p_hexagon.pointLeft.y && point1.y >= p_hexagon.pointUpLeft.y && point2.x == -1000)
	{
		normal = float2(p_hexagon.pointLeft.y - p_hexagon.pointUpLeft.y, -1 * (p_hexagon.pointLeft.x - p_hexagon.pointUpLeft.x));
		normal = normal.normalized();
		return true;
	}
	// Checking if the ball collision with the line in two points
	else if ((point1.x >= p_hexagon.pointLeft.x && point1.x <= p_hexagon.pointUpLeft.x && point1.y <= p_hexagon.pointLeft.y && point1.y >= p_hexagon.pointUpLeft.y)
		|| (point2.x >= p_hexagon.pointLeft.x && point2.x <= p_hexagon.pointUpLeft.x && point2.y <= p_hexagon.pointLeft.y && point2.y >= p_hexagon.pointUpLeft.y))
	{
		normal = float2(p_hexagon.pointLeft.y - p_hexagon.pointUpLeft.y, -1 *  (p_hexagon.pointLeft.x - p_hexagon.pointUpLeft.x));
		normal = normal.normalized();
		return true;
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
		// Return "null" for no intersection
		p_returnValue1 = float2(-1000, -1000);
		p_returnValue2 = float2(-1000, -1000);
	}
	else if (delta == 0) // One intersection
	{
		// Code for returning intersecting point
		u1 = -b / (2 * a);
		p_returnValue1 = p_point1 + (point2MinusPoint1 * u1);
		p_returnValue2 = float2(-1000, -1000);		// Return "null" for no intersect at second point
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

/// <summary> 
/// Generates a new direction for the ball if it hits the pad.
/// Returns (0,0) if there is no collision.
/// </summary>
float2 BOPhysics::BallPadCollision(sphere p_sphere, float2 p_sphereDir, sphere p_padSphere, double p_startAngle, double p_padSpread)
{
	// Return at once if the ball is outside the pad's outer radius or within the inner radius
	if (!CheckCollisionSpheres(p_sphere, p_padSphere))
	{
		return float2(0, 0);
	}
	if (CheckCollisionSpheres(p_sphere, sphere(p_padSphere.pos, p_padSphere.radius - 20)))
	{
		return float2(0, 0);
	}

	// Constants
	static const double degreesToRadians = (2 * PI) / 360;
	static const double rToDegrees = 360 / (2 * PI);

	float2 toSphereNormal = p_sphere.pos - p_padSphere.pos;
	double startAngle = p_startAngle * degreesToRadians;
	double padSpread = p_padSpread * degreesToRadians;

	// Convert to mathematical coordinate system
	double startAngleMA = (startAngle - HALF_PI) * -1;
	double normalized = startAngleMA;
	NormalizeAngle(normalized);

   	double padCenterAngle = startAngleMA - (padSpread / 2);
	NormalizeAngle(padCenterAngle);

	// Calculate a vector pointing towards the pad's center in SDL-Draw-Space
	float dirX = cos(padCenterAngle);
	float dirY = -sin(padCenterAngle);
	float2 padCenterVector = float2(dirX, dirY).normalized();

	// Calculate a vector from the center to the sphere
	float2 centerToSphere = (p_sphere.pos - p_padSphere.pos).normalized();
	centerToSphere.y *= -1;

	// Calculate the angle for the centerToSphere vector
	// Since acos has a period of PI, so some angles will need to be flipped
	float ctpAngle = acos(centerToSphere.x);
	if (centerToSphere.x < 0 && centerToSphere.y < 0)
	{
		ctpAngle *= -1;
	}
	if (centerToSphere.x > 0 && centerToSphere.y < 0)
	{
		ctpAngle *= -1;
	}
	NormalizeAngle(ctpAngle);
	NormalizeAngle(startAngleMA);

	// Check if the ball angle is within the borders of the pad
	if ((ctpAngle < startAngleMA) && (ctpAngle > (startAngleMA - padSpread)))
	{
		return CalculateNewDir(p_sphereDir, padCenterVector, padCenterAngle, padSpread / 2, ctpAngle);
	}

	// Special case when the pad is around the 0 area
	if ((startAngleMA - padSpread) < 0)
	{
		double padAngle = startAngleMA - padSpread + (2 * PI);

		if ((ctpAngle > 0) && (ctpAngle < startAngleMA) || ((ctpAngle > padAngle) && (ctpAngle < (2 * PI))))
	{
			return CalculateNewDir(p_sphereDir, padCenterVector, padCenterAngle, padSpread / 2, ctpAngle);
	}

	}
	return float2(0, 0);
}

/// <summary> 
/// Calculates the bounce around a biased angle
/// Returns (0,0) if there is no collision.
/// </summary>
float2 BOPhysics::CalculateNewDir(float2 currentDir, float2 padNormal, float p_padAngle, float p_maxWidthAngle, float p_ballAngle)
{
	// Bounce normals will be biased depending on the position of the pad that we bounce on.
	// biasAngle is the maximum bias, only reached at the edges of the pad
	static const float biasAngle = 1.57;

	// Amplify the ball and pad rotations by 2*PI to avoid 0-rotation problems
	float padAngleAmp = p_padAngle + 2 * PI;
	float ballAngleAmp = p_ballAngle + 2 * PI;

	// Calculate the percentage of our position from the pad center to edge
	float diffVal = (padAngleAmp - ballAngleAmp);
	diffVal /= -p_maxWidthAngle;
	// And create the actual diff by multiplying with the max bias
	float diff = diffVal * biasAngle;

	// Create a new, biased normal to bounce against
	float2 biasedNormal;
	biasedNormal.x = cos(padAngleAmp + diff);
	biasedNormal.y = -sin(padAngleAmp + diff);
	biasedNormal = biasedNormal.normalized();

	// Calculate the outgoing direction
	float vDotN = currentDir.dot(biasedNormal);
	float2 newDir = currentDir - (biasedNormal * vDotN * 2);

	return biasedNormal;
}

int BOPhysics::CheckCollisionBallShield(sphere p_sphere, sphere p_padSphere)
{
	float2 centerPad, centerBall;
	float padRadius, ballRadius;
	centerPad = p_padSphere.pos;
	centerBall = p_sphere.pos;
	padRadius = p_padSphere.radius;
	ballRadius = p_sphere.radius;
	if (CheckCollisionSpheres(p_sphere, p_padSphere))
	{
		if ((centerBall.x <= (centerPad.x + 80.0f)) && (centerBall.x >= (centerPad.x - 80.0f)) && (centerBall.y <= centerPad.y))
		{
			return 1;
		}
		else if ((centerBall.x <= (centerPad.x + 80.0f)) && (centerBall.x >= (centerPad.x - 80.0f)) && (centerBall.y >= centerPad.y))
		{
			return 2;
		}
		else if ((centerBall.y <= (centerPad.y + 80.0f)) && (centerBall.y >= (centerPad.y - 80.0f)) && (centerBall.x <= centerPad.x))
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

float2 BOPhysics::ReflectBallAroundNormal(float2 p_ballDir, float2 p_normal)
{
	float2 newBallDir, normal;
	float vDotN;
	newBallDir = p_ballDir;
	normal = p_normal;
	
	//Reflect direction
	// new vector = v -2(v.n)n
	vDotN = newBallDir.dot(p_normal);
	vDotN *= 2;
	normal = normal * vDotN;
	newBallDir = (newBallDir - normal);

	return newBallDir;
}

float2 BOPhysics::BlackHoleGravity(sphere p_ball, float2 p_ballDirection, float p_ballSpeed, sphere p_blackHole, double p_deltaTime)
{
	float2 newDirection = p_ballDirection;
	float2 center = float2(p_blackHole.pos - p_ball.pos); //En vektor mot hålet från bollen
	const double G = 0.000000000067;		//Gravitations konstant 6,7 * 10^-11

	float distanceAdjustment = CalculateDistance(p_ball.pos, p_blackHole.pos);// Beräkna radien mellan bollen och hålet
		
	double force = ((G * 5000000000000) / (distanceAdjustment*distanceAdjustment)); // F = G*M/R^2  -> Gravitations formel

	center = center.normalized();//Normaliserar vektorn mot hålet 
 	center = center * force;//Multiplicerar vektorn mot hålet med kraften

	
	newDirection = float2(newDirection.x * p_ballSpeed * p_deltaTime, newDirection.y * p_ballSpeed * p_deltaTime);//Beräknar längden av bollens riktningsvektor
	newDirection = float2(newDirection.x + center.x, newDirection.y + center.y);//Lägger på vektorn mot hålet

	return newDirection = newDirection.normalized();//Returnerar den normaliserade riktningsvektorn.
}

float BOPhysics::CalculateDistance(float2 p_Ball, float2 p_BlackHole)
{
	return sqrt(((p_Ball.x - p_BlackHole.x)*(p_Ball.x - p_BlackHole.x)) + ((p_Ball.y - p_BlackHole.y)*(p_Ball.y - p_BlackHole.y)));
}

float BOPhysics::CalculateBallFuel(float p_Fuel)
{
	return p_Fuel - 0.1f;
}
