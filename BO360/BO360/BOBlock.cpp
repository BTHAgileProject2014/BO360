#include "BOBlock.h"

BOBlock::BOBlock()
{
	dead = false;
    m_animated = false;
}

BOBlock::~BOBlock()
{

}

bool BOBlock::Initialize(float2 p_position, int2 p_size, SDL_Texture* p_sprite, PowerUpTypes p_powerup, int p_scoreValue)
{
	return Initialize(p_position, p_size, p_sprite, 1, p_powerup, p_scoreValue);
}

bool BOBlock::Initialize(float2 p_position, int2 p_size, SDL_Texture* p_sprite, int p_hp, PowerUpTypes p_powerup, int p_scoreValue)
{
	if (!BOObject::Initialize(p_position, p_size, p_sprite))
	{
		return false;
	}
	m_hp = p_hp;
	m_powerup = p_powerup;
	m_scoreValue = p_scoreValue;
	return true;
}

bool BOBlock::InitializeAnimated(float2 p_position, int2 p_size, int2 p_sourceSize, int p_frame, int p_maxFrames, double p_timePerFrame, bool p_hardReset, SDL_Texture* p_sprite, int p_hp, PowerUpTypes p_powerup, int p_scoreValue)
{
    if (!BOAnimatedObject::Initialize(p_position, p_size, p_sourceSize, p_frame, p_maxFrames, p_timePerFrame, p_hardReset, p_sprite))
    {
        return false;
    }

    m_hp = p_hp;
    m_powerup = p_powerup;
    m_scoreValue = p_scoreValue;
    m_animated = true;
    return true;
}

void BOBlock::Update(double p_deltaTime)
{
    m_glow.Animate(p_deltaTime);
}

box BOBlock::GetBoundingBox()
{
	return box(m_position, m_size);
}

hexagon BOBlock::GetBoundingHexagon()
{
	return hexagon(m_position, m_size);
}

void BOBlock::SetDead()
{
	dead = true;
}

bool BOBlock::GetDead()
{
	return dead;
}

PowerUpTypes BOBlock::GetPowerUp()
{
	return m_powerup;
}

int BOBlock::GetScore()
{
	return m_scoreValue;
}

bool BOBlock::Hit(int p_damage)
{
	m_hp -= p_damage;
	return m_hp < 1 ? true : false;
}

void BOBlock::AddGlow(float2 p_position, int2 p_size, int2 p_sourceSize, int p_frame, int p_numberOfFrames, double p_timePerFrame, bool p_hardReset, SDL_Texture* p_sprite)
{
    m_glow.Initialize(p_position, p_size, p_sourceSize, p_frame, p_numberOfFrames, p_timePerFrame, p_hardReset, p_sprite);
}

void BOBlock::DrawGlow()
{
    m_glow.DrawAnimated();
}

sphere BOBlock::GetBoundingSphere() const
{
	return sphere(m_position, m_radius + 10);
}