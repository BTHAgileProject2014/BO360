#ifndef BOBALL_H_
#define BOBALL_H_

#include "BOObject.h"

class BOBall: public BOObject
{
public:
	BOBall();
	~BOBall();

	void Update();
	void SetSpeed(float p_speed);
	float GetSpeed();
	void SetDirection(float2 p_direction);
	float2 GetDirection();

private:
	float m_speed;
	float2 m_direction;

};
#endif