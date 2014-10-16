#ifndef BOBLOCK_H_
#define BOBLOCK_H_

#include "BOAnimatedObject.h"

class BOBlock : public BOAnimatedObject
{
public:
	BOBlock();
	virtual ~BOBlock();
	bool Initialize(float2 p_position, int2 p_size, SDL_Texture* p_sprite, PowerUpTypes p_powerup, int p_scoreValue);
	bool Initialize(float2 p_position, int2 p_size, SDL_Texture* p_sprite, int p_hp, PowerUpTypes p_powerup, int p_scoreValue);

    bool InitializeAnimated(float2 p_position, int2 p_size, int2 p_sourceSize, int p_frame, int p_maxFrames, double p_timePerFrame, bool p_hardReset, SDL_Texture* p_sprite, int p_hp, PowerUpTypes p_powerup, int p_scoreValue);
    void AddGlow(float2 p_position, int2 p_size, int2 p_sourceSize, int p_frame, int p_numberOfFrames, double p_timePerFrame, bool p_hardReset, SDL_Texture* p_sprite);
    void Update(double p_deltaTime);

    sphere GetBoundingSphere() const;
	box GetBoundingBox() const;
	hexagon GetBoundingHexagon() const;
    void SetPosition(float2 p_position);
	void SetDead();
	bool GetDead();

	virtual bool Hit(int p_damage); // Returns true if dead

	PowerUpTypes GetPowerUp();

	int GetScore();
    bool IsAnimated() const;

    void Draw();

protected:
	PowerUpTypes SetRandomPowerUp();

    bool m_animated;
    bool m_hasGlow;
	int m_scoreValue;
	int m_hp;
	bool dead;
	PowerUpTypes m_powerup;
    BOAnimatedObject m_glow;
};
#endif