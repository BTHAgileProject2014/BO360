#include "BOPhysics.h"

const double BOPhysics::PI = 3.14159265359;
const double BOPhysics::HALF_PI = PI / 2;

float BOPhysics::m_timeScale;

bool BOPhysics::CheckCollisionSphereToSphere(const sphere &a, const sphere &b)
{
	return CollisionRadiusRadius(a.pos, a.radius, b.pos, b.radius);
}

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

bool BOPhysics::CheckCollisionSphereToHexagon(sphere p_sphere, hexagon p_hexagon, float2& p_normal)
{
	// Create 2 points for checking collision point on line
	float2 point1, point2;

	// Check collision with the sphere and each line in the hexagon
	// Same code 6 times with different points from the hexagon
	//					   __	
	//				      /  \
	//					  \__/
	// Upper Line _.
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointUpLeft, p_hexagon.pointUpRight, point1, point2);
	// Checking if collision in one point
	if (point1.x >= p_hexagon.pointUpLeft.x && point1.x <= p_hexagon.pointUpRight.x && point1.y == p_hexagon.pointUpLeft.y && point1.y == p_hexagon.pointUpRight.y && point2.x == -1000)
	{
		p_normal = float2(0, -1);
		p_normal = p_normal.normalized();
		
		return true;
	}
	// Checking if the ball collision with the line in two points
	else if ((point1.x >= p_hexagon.pointUpLeft.x && point1.x <= p_hexagon.pointUpRight.x && point1.y >= p_hexagon.pointUpLeft.y && point1.y >= p_hexagon.pointUpRight.y) 
		|| (point2.x >= p_hexagon.pointUpLeft.x && point2.x <= p_hexagon.pointUpRight.x && point2.y >= p_hexagon.pointUpLeft.y && point2.y >= p_hexagon.pointUpRight.y))
	{
		p_normal = float2(0, -1);
		p_normal = p_normal.normalized();
		return true;
	}
	
	// Upper right line \.
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointUpRight, p_hexagon.pointRight, point1, point2);
	// Checking if collision in one point
	if (point1.x >= p_hexagon.pointUpRight.x && point1.x <= p_hexagon.pointRight.x && point1.y >= p_hexagon.pointUpRight.y && point1.y <= p_hexagon.pointRight.y && point2.x == -1000)
	{
		p_normal = float2(0.86f, -0.50f);
		p_normal = p_normal.normalized();
		return true;
	}
	// Checking if the ball collision with the line in two points
	else if ((point1.x >= p_hexagon.pointUpRight.x && point1.x <= p_hexagon.pointRight.x && point1.y >= p_hexagon.pointUpRight.y && point1.y <= p_hexagon.pointRight.y)
		|| (point2.x >= p_hexagon.pointUpRight.x && point2.x <= p_hexagon.pointRight.x && point2.y >= p_hexagon.pointUpRight.y && point2.y <= p_hexagon.pointRight.y))
	{
		p_normal = float2(0.86f, -0.50f);
		p_normal = p_normal.normalized();
		return true;
	}
	
	// Lower right line /.
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointRight, p_hexagon.pointDownRight, point1, point2);
	// Checking if collision in one point
	if (point1.x <= p_hexagon.pointRight.x && point1.x >= p_hexagon.pointDownRight.x && point1.y >= p_hexagon.pointRight.y && point1.y <= p_hexagon.pointDownRight.y && point2.x == -1000)
	{
		p_normal = float2(0.84f, 0.53f);
		p_normal = p_normal.normalized();
		return true;
	}
	// Checking if the ball collision with the line in two points
	else if ((point1.x <= p_hexagon.pointRight.x && point1.x >= p_hexagon.pointDownRight.x && point1.y >= p_hexagon.pointRight.y && point1.y <= p_hexagon.pointDownRight.y)
		|| (point2.x <= p_hexagon.pointRight.x && point2.x >= p_hexagon.pointDownRight.x && point2.y >= p_hexagon.pointRight.y && point2.y <= p_hexagon.pointDownRight.y))
	{
		p_normal = float2(0.84f, 0.53f);
		p_normal = p_normal.normalized();
		return true;
	}
	
	// Lower middle line _.
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointDownRight, p_hexagon.pointDownLeft, point1, point2);
	// Checking if collision in one point
	if (point1.x <= p_hexagon.pointDownRight.x && point1.x >= p_hexagon.pointDownLeft.x && point1.y >= p_hexagon.pointDownRight.y && point1.y <= p_hexagon.pointDownLeft.y && point2.x == -1000)
	{
		p_normal = float2(0, 1);
		p_normal = p_normal.normalized();
		return true;
	}
	// Checking if the ball collision with the line in two points
	else if ((point1.x <= p_hexagon.pointDownRight.x && point1.x >= p_hexagon.pointDownLeft.x && point1.y >= p_hexagon.pointDownRight.y && point1.y <= p_hexagon.pointDownLeft.y)
		|| (point2.x <= p_hexagon.pointDownRight.x && point2.x >= p_hexagon.pointDownLeft.x && point2.y >= p_hexagon.pointDownRight.y && point2.y <= p_hexagon.pointDownLeft.y))
	{
		p_normal = float2(0, 1);
		p_normal = p_normal.normalized();
		return true;
	}
	
	// Lower Left line \.
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointDownLeft, p_hexagon.pointLeft, point1, point2);
	// Checking if collision in one point

	if (point1.x <= p_hexagon.pointDownLeft.x && point1.x >= p_hexagon.pointLeft.x && point1.y <= p_hexagon.pointDownLeft.y && point1.y >= p_hexagon.pointLeft.y && point2.x == -1000)
	{
		p_normal = float2(-0.84f, 0.53f);
		p_normal = p_normal.normalized();
		return true;
	}
	// Checking if the ball collision with the line in two points
	else if ((point1.x <= p_hexagon.pointDownLeft.x && point1.x >= p_hexagon.pointLeft.x && point1.y <= p_hexagon.pointDownLeft.y && point1.y >= p_hexagon.pointLeft.y)
		|| (point2.x <= p_hexagon.pointDownLeft.x && point2.x >= p_hexagon.pointLeft.x && point2.y <= p_hexagon.pointDownLeft.y && point2.y >= p_hexagon.pointLeft.y))
	{
		p_normal = float2(-0.84f, 0.53f);
		p_normal = p_normal.normalized();
		return true;
	}

	// Upper left line /.
	CheckCollisionSphereToLine(p_sphere, p_hexagon.pointLeft, p_hexagon.pointUpLeft, point1, point2);
	// Checking if collision in one point
	if (point1.x >= p_hexagon.pointLeft.x && point1.x <= p_hexagon.pointUpLeft.x && point1.y <= p_hexagon.pointLeft.y && point1.y >= p_hexagon.pointUpLeft.y && point2.x == -1000)
	{
		p_normal = float2(-0.86f, -0.50f);
		p_normal = p_normal.normalized();
		return true;
	}
	// Checking if the ball collision with the line in two points
	else if ((point1.x >= p_hexagon.pointLeft.x && point1.x <= p_hexagon.pointUpLeft.x && point1.y <= p_hexagon.pointLeft.y && point1.y >= p_hexagon.pointUpLeft.y)
		|| (point2.x >= p_hexagon.pointLeft.x && point2.x <= p_hexagon.pointUpLeft.x && point2.y <= p_hexagon.pointLeft.y && point2.y >= p_hexagon.pointUpLeft.y))
	{
		p_normal = float2(-0.86f, -0.50f);
		p_normal = p_normal.normalized();
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
	if (!CollisionRadiusRadius(p_sphere.pos, p_sphere.radius, p_padSphere.pos, p_padSphere.radius))
	{
		return float2(0, 0);
	}
	if (CollisionRadiusRadius(p_sphere.pos, p_sphere.radius, p_padSphere.pos, p_padSphere.radius - 20))
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
	float dirX = (float)cos(padCenterAngle);
	float dirY = (float)-sin(padCenterAngle);
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
		return CalculateNewDir(p_sphereDir, (float)padCenterAngle, (float)padSpread / 2.0f, ctpAngle);
	}

	// Special case when the pad is around the 0 area
	if ((startAngleMA - padSpread) < 0)
	{
		double padAngle = startAngleMA - padSpread + (2 * PI);

		if ((ctpAngle > 0) && (ctpAngle < startAngleMA) || ((ctpAngle > padAngle) && (ctpAngle < (2 * PI))))
		{
			return CalculateNewDir(p_sphereDir, (float)padCenterAngle, (float)padSpread / 2.0f, ctpAngle);
		}

	}
	return float2(0, 0);
}

/// <summary> 
/// Calculates the bounce around a biased angle
/// Returns (0,0) if there is no collision.
/// </summary>
float2 BOPhysics::CalculateNewDir(float2 p_currentDir, float p_padAngle, float p_maxWidthAngle, float p_ballAngle)
{
	// Bounce normals will be biased depending on the position of the pad that we bounce on.
	// biasAngle is the maximum bias, only reached at the edges of the pad
	static const float biasAngle = 1.57f;

	// Amplify the ball and pad rotations by 2*PI to avoid 0-rotation problems
	float padAngleAmp = p_padAngle + 2.0f * (float)PI;
	float ballAngleAmp = p_ballAngle + 2.0f * (float)PI;

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
	float vDotN = p_currentDir.dot(biasedNormal);
	float2 newDir = p_currentDir - (biasedNormal * vDotN * 2);

	return biasedNormal;
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
	if (vDotN > -1 && vDotN < 0)
	{
		vDotN *= 2;
		normal = normal * vDotN;
		newBallDir = (newBallDir - normal);
	}
	return newBallDir;
}

void BOPhysics::BallToBallCollision(BOBall& ball1, BOBall& ball2)
{
	float2 direction1, direction2;
	float2 position1, position2;
	float2 normal1, normal2;

	direction1 = ball1.GetDirection();
	direction2 = ball2.GetDirection();
	position1 = ball1.GetPosition();
	position2 = ball2.GetPosition();

	normal1 = float2(position2.x - position1.x, position2.y - position1.y);    
	normal2 = float2(position1.x - position2.x, position1.y - position2.y);
    normal1.normalize();
    normal2.normalize();
	ball1.SetDirection(ReflectBallAroundNormal(direction1, normal2));
	ball2.SetDirection(ReflectBallAroundNormal(direction2, normal1));
}

bool BOPhysics::BallToSphereCollision(BOBall& p_ball, sphere p_sphere)
{
    float2 position1, position2;
    float radius1, radius2;
    float2 normal;

    position1 = p_ball.GetPosition();
    position2 = p_sphere.pos;
    radius1 = p_ball.GetBoundingSphere().radius;
    radius2 = p_sphere.radius;
    if (CollisionRadiusRadius(position1, radius1, position2, radius2))
    {
        float2 normal = float2(position1.x - position2.x, position1.y - position2.y);
        normal.normalize();
        p_ball.SetDirection(ReflectBallAroundNormal(p_ball.GetDirection(), normal));
        
        return true;
    }

    return false;
}

float2 BOPhysics::ApplyGravity(float2 p_position, float2 p_direction, float p_speed, float p_influenceFactor, float2 p_blackHolePos, double p_deltaTime)
{
    float2 gravityDirection = p_blackHolePos - p_position;
    float distance = gravityDirection.length();
    gravityDirection.normalize();

    distance *= 0.05f;

    const double GravityFactor = p_deltaTime * 100000;
    double force = (GravityFactor * p_influenceFactor) / (distance * distance);

    float2 newDir = p_direction * p_speed + gravityDirection * (float)force;
    return newDir.normalized();
}

// Gravity calculation
float2 BOPhysics::BlackHoleGravity(sphere p_ball, float2 p_ballDirection, float p_ballSpeed, sphere p_blackHole, double p_deltaTime)
{
    //std::cout << p_deltaTime << std::endl;
	float2 newDirection = p_ballDirection;
	float2 center = float2(p_blackHole.pos - p_ball.pos); //En vektor mot h�let fr�n bollen
	const double G = 0.67;		//Gravitations konstant 6,7 * 10^-11	//Tar bort nollor fr�n G och massa f�r att l�ttare se	//0.000000000067

	float distanceAdjustment = CalculateDistance(p_ball.pos, p_blackHole.pos);// Ber�kna radien mellan bollen och h�let
		
	double force = ((G * p_ballSpeed) / (distanceAdjustment*distanceAdjustment)); // F = G*M/R^2  -> Gravitations formel		//5000000000000

	center = center.normalized();//Normaliserar vektorn mot h�let 
	center = center * (float)force * (float)p_deltaTime * 2000;//Multiplicerar vektorn mot h�let med kraften
	
	newDirection = float2(newDirection.x * (p_ballSpeed * (float)p_deltaTime) + center.x, newDirection.y * (p_ballSpeed * (float)p_deltaTime) + center.y);//Ber�knar l�ngden av bollens riktningsvektor

	return newDirection = newDirection.normalized();//Returnerar den normaliserade riktningsvektorn.
}

float BOPhysics::CalculateDistance(float2 p_ball, float2 p_blackHole)
{
	return sqrt(((p_ball.x - p_blackHole.x)*(p_ball.x - p_blackHole.x)) + ((p_ball.y - p_blackHole.y)*(p_ball.y - p_blackHole.y)));
}

// Fuel Calculation
float BOPhysics::CalculateBallFuel(float p_fuel, double p_deltaTime)
{
	return p_fuel - (float)(1.0f * p_deltaTime);
}

// Shield Collision Calculation
int BOPhysics::CheckCollisionBallShield(sphere p_sphere, sphere p_padSphere)
{
	//Change to new ball ball collision when it is done.
	float2 centerPad, centerBall;
	float padRadius, ballRadius;
	centerPad = p_padSphere.pos;
	centerBall = p_sphere.pos;
	padRadius = p_padSphere.radius;
	ballRadius = p_sphere.radius;
	if (CollisionRadiusRadius(p_sphere.pos, p_sphere.radius, p_padSphere.pos, p_padSphere.radius))
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

bool BOPhysics::BallBouncedOnPad(const BOBall &p_ball, const BOPaddle &p_paddle, float2& p_newDirection)
{
	float2 ballPosition = p_ball.GetPosition();
	float2 ballDirection = p_ball.GetDirection();
	float2 paddleRotationCenter = p_paddle.GetPosition();
	float2 centerToBall = ballPosition - paddleRotationCenter;
	
	// Check if the ball is in range with the paddle
	// Return at once if the ball is outside the pad's outer radius
	if (!CheckCollisionSphereToSphere(p_ball.GetBoundingSphere(), p_paddle.GetBoundingSphere()))
	{
		return false;
	}
	// Or if it is within the inner radius
	sphere innerSphere = p_paddle.GetBoundingSphere();
	innerSphere.radius -= 20;
	if (CheckCollisionSphereToSphere(p_ball.GetBoundingSphere(), innerSphere))
	{
		return false;
	}

	// Check if the ball hit the paddle portion
    double padStartRad = p_paddle.GetStartRotation() * DEGREES_TO_RADIANS;
    NormalizeAngle(padStartRad);
    double degrees = p_paddle.GetDegrees();
    if (degrees > 359.99)
    {
        degrees = 359.99;
    }
    double angleRad =  degrees * DEGREES_TO_RADIANS;
    double padEndRad = padStartRad + angleRad;
    NormalizeAngle(padEndRad);

	double ballAngleRad = acos(centerToBall.normalized().x);

    // Move to the same coordinate system as SDL rotations
    if (centerToBall.y < 0)
    {
        ballAngleRad *= -1;
    }
    ballAngleRad += HALF_PI; 
    NormalizeAngle(ballAngleRad);

    if (!IsWithinRad(padStartRad, padEndRad, ballAngleRad))
    {
        return false;
    }

	// Reflect around the normal
	p_newDirection = Reflect(ballDirection, centerToBall);

	// Apply bias (?)
    float2 bias = ApplyBias(padStartRad, padEndRad, ballAngleRad);
    p_newDirection = p_newDirection + bias;
    p_newDirection.normalize();

	return true;
}

// Calculates the angle in degrees from p_v1 to p_v2 in SDL rotation coordinate system
double BOPhysics::AngleBetweenDeg(const float2& p_v1, const float2& p_v2)
{
    return RADIANS_TO_DEGREES * AngleBetweenRad(p_v1, p_v2);
}

// Calculates the angle in radians from p_v1 to p_v2 in SDL rotation coordinate system
double BOPhysics::AngleBetweenRad(const float2& p_v1, const float2& p_v2)
{

    float2 v1 = p_v1.normalized();
    float2 v2 = p_v2.normalized();
    v1.y *= -1;
    v2.y *= -1;

    // 1. Convert from vectors to angles
    double v1AngleRad = acos(v1.normalized().x);
    double v2AngleRad = acos(v2.normalized().x);

    // Move to the same coordinate system as SDL rotations
    if (v1.y < 0)
    {
        v1AngleRad *= -1;
    }
    v1AngleRad += HALF_PI;
    NormalizeAngle(v1AngleRad);

    if (v2.y < 0)
    {
        v2AngleRad *= -1;
    }
    v2AngleRad += HALF_PI;
    NormalizeAngle(v2AngleRad);

    // 2. Account for near-origo issues
    if (v1AngleRad > v2AngleRad) // Around origo
    {
        v2AngleRad += PI * 2.0; // Forward a full rotation
    }

    // 3. Calculate the actual angle
    double resultAngle = 2 * PI - (v2AngleRad - v1AngleRad);
    return resultAngle;
}

float2 BOPhysics::Reflect(const float2 p_target, const float2 p_normal)
{
	float2 normal = p_normal.normalized();
	float2 direction = p_target.normalized();
	float vDotN = direction.dot(normal);
	
	if (vDotN < 0) // Check that we hit from the right side
	{
		direction = p_target.normalized();
		vDotN = direction.dot(normal);
		float2 reflected = direction - (normal * vDotN * 2.0);
		return reflected.normalized();
	}
	return p_target;
}

bool BOPhysics::IsWithinRad(double p_start, double p_end, double p_toTest)
{
    double originalEnd = p_end;

    if (p_start > p_end) // Around origo
    {
        p_end += PI * 2.0; // Forward a full rotation

        // If toTest was between 0 and p_end, we need to forward it too
        if (p_toTest < originalEnd)
        {
            p_toTest += PI * 2.0;
        }
    }

    // toTest should now always be within start and end's numbers if it is actually within their angles

    return (p_start < p_toTest
        && p_toTest < p_end);
}

float2 BOPhysics::ApplyBias(double p_start, double p_end, double p_ball)
{
    double start = p_start;
    double end = p_end;
    double ball = p_ball;

    if (start > end) // Around origo
    {
        end += PI * 2.0; // Forward a full rotation

        // If toTest was between 0 and p_end, we need to forward it too
        if (ball < p_end)
        {
            ball += PI * 2.0;
        }
    }

    // calculate the ball bias (-1 to 1)
    double center = (end + start) / 2;
    double maxDistance = end - center;
    double ballRelativeToPadCenter = ball - center;
    double ballBias = ballRelativeToPadCenter / (maxDistance * 0.8);
    if (abs(ballBias) > 1)
    {
        ballBias /= abs(ballBias);
    }

    // Scale worst case bias with paddle size
    // The constant can be scaled for more extreme angles
    float worstCaseBias = 0.5 + maxDistance;//1.2f;

    // Calculate the bias angle for this bounce
    double biasAngle = center + ballBias * worstCaseBias;

    // Turn into vector
    float2 biasVector;
    biasVector.x = (float)sin(biasAngle);
    biasVector.y = (float)-cos(biasAngle);
    biasVector.normalize();

    // Scale with an influence factor
    float influenceFactor = 1.0f;
    return biasVector * influenceFactor;
}

float BOPhysics::GetTimeScale()
{
    return m_timeScale;
}

void BOPhysics::SetTimeScale(float p_timeScale)
{
    m_timeScale = p_timeScale;
}