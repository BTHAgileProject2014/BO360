#ifndef BOBALL_H_
#define BOBALL_H_

#include "BOObject.h"

class BOBall: public BOObject
{
public:
	BOBall();
	~BOBall();
	bool Initialize(float2 p_position, int2 p_size, std::string p_fileName, float p_speed, float2 p_direction);
	void Update();
	void SetSpeed(float p_speed);
	float GetSpeed();
	void SetDirection(float2 p_direction);
	float2 GetDirection();
	sphere GetBoundingSphere();

private:
	float m_speed;
	float2 m_direction;

};
#endif