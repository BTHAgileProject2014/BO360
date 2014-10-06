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
	bool Initialize(float2 p_position, int2 p_size, SDL_Texture* p_sprite, float p_speed, float2 p_direction, int2 p_windowSize);
	void Update(double p_deltaTime, sphere p_blackHoleBounds);

	void Move(double p_deltaTime, sphere p_blackHoleBounds);
	void SetPosition(float2 p_position);

	void SetSpeed(float p_speed);
	float GetSpeed();

	void SetDirection(float2 p_direction);
	float2 GetDirection()const;
    void ActivateShockwave();

	float GetFuel();
	void SetFuel(float p_Fuel);

	bool CanColide();
	box GetBoundingBox();
	int GetDamage();

	void BouncedOnPad();
	void BouncedOnHexagon();

	void Handle(InputMessages p_inputMessages);

	bool IsStuckToPad();
	void SetStuckToPad(bool p_stuck);
	void SetBallOnFire(bool p_setOnFire);
	bool IsOnFire() const;

private:
	int m_damage;
	bool m_canColide;
	float m_speed;
	float2 m_direction;
	bool m_mouseCheat;
	int2 m_windowSize;
	float m_Fuel;
	bool m_stuckToPad;
	bool m_onFire;
	double m_fireTimeElapsed;
	const double m_fireTimeDuration = 5; // 5 seconds for fireball duration

	SDL_Texture* m_sprite2;
	SDL_Texture* m_sprite3;
	SDL_Texture* m_sprite4;
};
#endif