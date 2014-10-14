#ifndef BOBALL_H_
#define BOBALL_H_

#include "BOAnimatedObject.h"
#include "BOSubscriber.h"
#include "BOPhysics.h"


class BOBall: public BOObject, public BOSubscriber
{
public:
	BOBall();
	~BOBall();
	bool Initialize(float2 p_position, int2 p_size, SDL_Texture* p_sprite, float p_speed, float2 p_direction, int2 p_windowSize);
	void Update(double p_deltaTime, sphere p_blackHoleBounds, bool p_won);
    void DrawBallWithTail();

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
    float GetStuckAngle()const;
    void SetStuckAngle(float p_stuckAngle);
	bool HasBallCollidedWithBall() const;
	void SetBallCollidedWithBall(bool p_collided);
	bool GetNewlyLaunched();
	bool IsSpawned();

private:
	int m_damage;
	bool m_canColide;
	float m_speed;
	float2 m_direction;
	bool m_mouseCheat;
	int2 m_windowSize;
	float m_Fuel;
	bool m_onFire;
	bool m_hasCollidedWithBall;
	double m_fireTimeElapsed;
	double m_fireTimeDuration; // 10 seconds for fireball duration
    bool m_stuckToPad;
	bool m_stuckToPadPrev;
    float m_stuckAngle;
	bool m_newlyLaunched;
	bool m_newlyLaunchedPrev;
    bool m_rocketEngine;
	bool m_spawned;

    double m_rotation;
    BOAnimatedObject m_thruster;
    SDL_Texture* m_fireBallTexture;
};
#endif