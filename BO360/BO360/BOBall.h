#ifndef BOBALL_H_
#define BOBALL_H_

#include "BOObject.h"
#include "BOSubscriber.h"
#include "BOPhysics.h"

class BOBall: public BOObject, public BOSubscriber
{
public:
	BOBall();
	~BOBall();
	bool Initialize(float2 p_position, int2 p_size, std::string p_fileName, float p_speed, float2 p_direction, int2 p_windowSize);
	void Update(double p_deltaTime, sphere p_blackHoleBounds);
	void SetSpeed(float p_speed);
	float GetSpeed();
	void SetDirection(float2 p_direction);
	float2 GetDirection() const;
	bool CanColide();
	void BouncedOnPad();
	box GetBoundingBox();
	void Handle(InputMessages p_inputMessages);
	void BouncedOnHexagon();
	float GetFuel();
	void SetFuel(float p_Fuel);
	int GetDamage();
	void Move(double p_deltaTime, sphere p_blackHoleBounds);
	bool IsStuckToPad();
	void SetStuckToPad(bool p_stuck);
	void SetPosition(float2 p_position);

private:
	int m_damage;
	bool m_canColide;
	float m_speed;
	float2 m_direction;
	bool m_mouseCheat;
	int2 m_windowSize;
	float m_Fuel;
	bool m_stuckToPad;
	SDL_Texture* m_sprite2,*m_sprite3;
};
#endif