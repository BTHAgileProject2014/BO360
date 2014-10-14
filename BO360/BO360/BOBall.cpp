#include "BOBall.h"

BOBall::BOBall()
{

}

BOBall::~BOBall()
{

}

bool BOBall::Initialize(float2 p_position, int2 p_size, SDL_Texture* p_sprite, float p_speed, float2 p_direction, int2 p_windowSize)
{
    if (!BOObject::Initialize(p_position, p_size, p_sprite))
	{
		return false;
	}
	m_damage = 1;
    m_rocketEngine = false;
	m_Fuel = 0.0f;
	m_canColide = true;
	m_speed = p_speed * BOTechTreeEffects::BallEffects.speed;
	m_direction = p_direction.normalized();
	m_windowSize = p_windowSize;
	m_stuckToPad = true;
	m_onFire = false;
	m_fireTimeElapsed = 0; // Set duration for fireball powerup in header, const variable
    m_rotation = 0;

	// Load texture.
	m_sprite = p_sprite;
	m_fireBallTexture = BOTextureManager::GetTexture(TEXFIREBALL);
    m_thruster.Initialize(p_position, int2(41, 41), int2(41, 41), 0, 2, 0, true, BOTextureManager::GetTexture(TEXBALLTAIL));

	m_mouseCheat = false;

    m_stuckAngle = 42;

	m_newlyLaunched = false;

	return true;
}

void BOBall::Update(double p_deltaTime, sphere p_blackHoleBounds)
{
    // Move if the ball is not stuck
	if (!m_stuckToPad && !m_mouseCheat)
	{
		Move(p_deltaTime, p_blackHoleBounds);
	}

    // Tick timer for fire powerup
	if (m_onFire)
	{
		m_fireTimeElapsed += p_deltaTime * BOPhysics::GetTimeScale();
		if (m_fireTimeElapsed >= m_fireTimeDuration)
		{
			SetBallOnFire(false);
            m_fireTimeElapsed = 0;
		}
	}
    m_thruster.SetPosition(m_position);
    m_rotation = BOPhysics::AngleBetweenDeg(float2(0, 1), m_direction) + 180;
    if (!m_stuckToPad && m_stuckToPadPrev && BOTechTreeEffects::UtilityEffects.PUGiftEnabled)
    {
        m_newlyLaunched = true;
    }
    else
    {
        m_newlyLaunched = false;
    }
    m_stuckToPadPrev = m_stuckToPad;
}
	

void BOBall::DrawBallWithTail()
{
    m_thruster.SetRotation(m_rotation);
    m_thruster.DrawAnimated();

    int4 source = int4(0, 0, m_size.x, m_size.y);
    int4 destination = int4((int)(m_position.x - m_scale * (m_size.x / 2)), (int)(m_position.y - m_scale * (m_size.y / 2)), (int)(m_scale * m_size.x), (int)(m_scale * m_size.y));
    BOGraphicInterface::DrawEx(m_sprite, source, destination, m_rotation, int2(7, 7), m_opacity);

    if (m_onFire)
    {
        source = int4(0, 0, 25, 25);
        destination = int4((int)(m_position.x - m_scale * (25 / 2)), (int)(m_position.y - m_scale * (25 / 2)), (int)(m_scale * 25), (int)(m_scale * 25));
        BOGraphicInterface::DrawEx(m_fireBallTexture, source, destination, 0, int2(0, 0), m_opacity);
    }
}

void BOBall::SetSpeed(float p_speed)
{
	m_speed = p_speed;
}

float BOBall::GetSpeed()
{
	return m_speed;
}

void BOBall::SetDirection(float2 p_direction)
{
	if (!(p_direction.x == 0 && p_direction.y == 0))
	{
		m_direction = p_direction.normalized();
	}
}

float2 BOBall::GetDirection()const
{
	return m_direction;
}

bool BOBall::CanColide()
{
	return m_canColide;
}

void BOBall::BouncedOnPad()
{
    m_rocketEngine = true;
	m_Fuel = 1.0f;
}

box BOBall::GetBoundingBox()
{
	return box(m_position, m_size);
}

void BOBall::Handle(InputMessages p_inputMessages)
{
	if (p_inputMessages.upArrow)
	{
		if (m_mouseCheat)
		{
			m_mouseCheat = false;
		}
		else
		{
			m_mouseCheat = true;
		}
	}
	if (m_mouseCheat)
	{
		m_position.x = (float)p_inputMessages.mouseX;
		m_position.y = (float)p_inputMessages.mouseY;
	}
}

void BOBall::BouncedOnHexagon()
{
    m_rocketEngine = false;
	m_canColide = true;
}

float BOBall::GetFuel()
{
	return m_Fuel;
}
void BOBall::SetFuel(float p_fuel)
{
	m_Fuel = p_fuel;
}

int BOBall::GetDamage()
{
    if (m_onFire)
    {
        return m_damage * 2;
    }
    else
    {
	return m_damage;
}

}

bool BOBall::IsStuckToPad()
{
	return m_stuckToPad;
}

void BOBall::SetStuckToPad(bool p_stuck)
{
	m_stuckToPad = p_stuck;
}

void BOBall::Move(double p_deltaTime, sphere p_blackHoleBounds)
{
    float timescale = BOPhysics::GetTimeScale();

	if (m_Fuel > 0)
	{
        m_Fuel -= (float)p_deltaTime * timescale * 0.5f;
        m_thruster.SetFrame(0);
    }
    else
    {
        m_thruster.SetFrame(1);
    }
    
    float speedFactor = 2.0f;

    float2 newDir = BOPhysics::ApplyGravity(m_position, m_direction, m_speed, 1.0f - m_Fuel, p_blackHoleBounds.pos, p_deltaTime * timescale);
    m_direction = newDir;
    m_position = m_position + (m_direction * m_speed * p_deltaTime * timescale);
    /*
    if (m_rocketEngine)
    {
		m_position.x = (float)(speedFactor * m_speed * p_deltaTime) * m_direction.x + m_position.x;
		m_position.y = (float)(speedFactor * m_speed * p_deltaTime) * m_direction.y + m_position.y;
		if (!m_onFire)
		{
			m_sprite = m_sprite2;
		}			
	else
	{
		m_position.x = (float)(speedFactor * m_speed * p_deltaTime) * m_direction.x + m_position.x;
		m_position.y = (float)(speedFactor * m_speed * p_deltaTime) * m_direction.y + m_position.y;
		

        float2 newDir = BOPhysics::ApplyGravity(m_position, m_direction, m_speed, 1.0f - m_Fuel, p_blackHoleBounds.pos, p_deltaTime);
        m_direction = newDir;
    //    newDir = newDir + m_direction;
    //    SetDirection(newDir.normalized());
       //SetDirection(BOPhysics::BlackHoleGravity(GetBoundingSphere(), GetDirection(), GetSpeed(), p_blackHoleBounds, p_deltaTime));
		if (!m_onFire)
		{
		m_sprite = m_sprite3;
		}
	}
    */

	if (m_position.x < (m_size.x / 2) || m_position.x >(m_windowSize.x - (m_size.x / 2)))
	{
		m_Fuel = 0;
		m_canColide = true;
		m_direction.x *= -1;
	}
	if (m_position.y < (m_size.y / 2) || m_position.y >(m_windowSize.y - (m_size.y / 2)))
	{
		m_Fuel = 0;
		m_canColide = true;
		m_direction.y *= -1;
	}
}

void BOBall::SetPosition(float2 p_position)
{
	if (m_stuckToPad)
	{
		int2 windowSize = BOGraphicInterface::GetWindowSize();
		m_direction = p_position - float2((windowSize.x * 0.5f), (windowSize.y *0.5f));
		m_direction.normalize();
		p_position.x += m_direction.x * 8;
		p_position.y += m_direction.y * 8;
	}
	BOObject::SetPosition(p_position);
}
float BOBall::GetStuckAngle() const
{
    return m_stuckAngle;
}
void BOBall::SetStuckAngle(float p_stuckAngle)
{
	if (p_stuckAngle > 360)
	{
		p_stuckAngle -= 360;
	}
	else if (p_stuckAngle < 0)
	{
		p_stuckAngle += 360;
	}
    m_stuckAngle = p_stuckAngle;
}
// input false for fire off: true for fire on
void BOBall::SetBallOnFire(bool p_setOnFire)
{
	if (p_setOnFire)
	{
		m_onFire = true;
	}
	else if (!p_setOnFire)
	{
		m_onFire = false;
	}
}

bool BOBall::IsOnFire() const
{
	return m_onFire;
}

void BOBall::ActivateShockwave()
{
    m_Fuel += 0.5f;
    float2 direction = float2();
    direction.x = GetPosition().x - m_windowSize.x * 0.5f;
    direction.y = GetPosition().y - m_windowSize.y * 0.5f;
    direction.normalize();
    SetDirection(direction);
}

bool BOBall::HasBallCollidedWithBall() const
{
	return m_hasCollidedWithBall;
}

void BOBall::SetBallCollidedWithBall(bool p_collided)
{
	m_hasCollidedWithBall = p_collided;
}

bool BOBall::GetNewlyLaunched()
{
	return m_newlyLaunched;
}
