#ifndef BOBALL_H_
#define BOBALL_H_

#include "BOObject.h"
#include "BOSubscriber.h"

class BOBall: public BOObject, public BOSubscriber
{
public:
	BOBall();
	~BOBall();
	bool Initialize(float2 p_position, int2 p_size, std::string p_fileName, float p_speed, float2 p_direction, int2 p_windowSize);
	void Update(Uint32 p_deltaTime);
	void SetSpeed(float p_speed);
	float GetSpeed();
	void SetDirection(float2 p_direction);
	float2 GetDirection();
	bool CanColide();
	void BouncedOnPad();
	void BouncedOnHexa();
	box GetBoundingBox();
	void Handle(InputMessages p_inputMessages);

private:
	bool m_canColide;
	float m_speed;
	float2 m_direction;
	bool m_mouseCheat;
	int2 m_windowSize;
};
#endif