#include "BOPaddle.h"

BOPaddle::BOPaddle()
{

}

BOPaddle::~BOPaddle()
{

}

bool BOPaddle::Initialize(float2 p_position, int2 p_size, SDL_Texture* p_sprite)
{
    m_isSticky = false;
	m_rotation = 0.0f;
	m_totalDegrees = 21.2;
	m_segementDegree = m_totalDegrees;
	m_segments = 1;
	AddSegments(2);
	m_deltaRotation = 200 * BOTechTreeEffects::PaddleEffects.speed;
	BOPublisher::AddSubscriber(this);
	BOPowerUpManager::AddSubscriber(this);
	return BOObject::Initialize(p_position, p_size, p_sprite);
	
}

void BOPaddle::Handle(InputMessages p_inputMessages)
{
	if (p_inputMessages.leftArrow)
	{
		m_movingLeft = true;
	}
	else
	{
		m_movingLeft = false;
	}

	if (p_inputMessages.rightArrow)
	{
		m_movingRight = true;
	}
	else
	{
		m_movingRight = false;
	}

	if (p_inputMessages.zKey)
	{
			//RemoveSegments(1);
	}
	if (p_inputMessages.xKey)
	{
			//AddSegments(1);
	}
}

void BOPaddle::Handle(PowerUpTypes p_type, bool p_activated)
{
	switch (p_type)
	{
		case PUBiggerPad:
		{
			if (p_activated)
			{
				// Make the paddle bigger
				if (m_segments < 5)
				{
					AddSegments(1);
				}
			}

			else
			{
				// Revert to normal paddle
			}

			break;
		}
		
		case PUSmallerPad:
		{
			if (p_activated)
			{
				// Make the paddle smaller
				RemoveSegments(1);
			}
			else
			{
				// Revert to normal paddle
			}

			break;
		}
	}
}

void BOPaddle::Update(double p_deltaTime)
{
	if (m_movingLeft)
	{
		m_rotation -= m_deltaRotation * p_deltaTime;

		if (m_rotation < 0)
		{
			m_rotation += 360;
		}
	}

	else if (m_movingRight)
	{
		m_rotation += m_deltaRotation * p_deltaTime;

		if (m_rotation > 360)
		{
			m_rotation -= 360;
		}
	}
}

void BOPaddle::Draw()
{
	int4 mySource = int4(0, 0, m_size.x, m_size.y);
	int4 myDest = int4((int)m_position.x - (m_size.x / 2), (int)m_position.y - (m_size.y / 2), m_size.x, m_size.y);

	for (int i = 0; i < m_segments; i++)
	{
		BOGraphicInterface::DrawEx(m_sprite, mySource, myDest, m_rotation + ((double)m_segementDegree * i), int2(m_size.x / 2, m_size.y / 2));
	}
}

double BOPaddle::GetRotation()const
{
	return m_rotation;
}

double BOPaddle::GetStartRotation()const
{
    return m_rotation - (m_segementDegree / 2) - 4;
}

int BOPaddle::GetSegments()const
{
	return m_segments;
}

void BOPaddle::AddSegments(int p_segments)
{
	if (m_segments < 17)
	{
		m_totalDegrees = m_totalDegrees + (m_segementDegree * p_segments);
		m_segments += p_segments;
	}
}

void BOPaddle::RemoveSegments(int p_segments)
{
	if (m_segments > 1)
	{
		m_totalDegrees = m_totalDegrees - (m_segementDegree * p_segments);
		m_segments -= p_segments;
	}
}

double BOPaddle::GetDegrees()const
{
	return m_totalDegrees + 8;
}

float2 BOPaddle::GetBallSpawnPosition()
{
    float radius = (m_size.x * 0.5f);
    float alpha = (float)(((-m_rotation - (21 * (m_segments - 1))) * DEGREES_TO_RADIANS) + 2);
    float ballPosx = cos(alpha) * radius;
    float ballPosy = sin(alpha) * radius;

    float tempx = m_position.x + ballPosx;
    float tempy = m_position.y - ballPosy;

    return float2(tempx, tempy);
}

float2 BOPaddle::GetBallStuckPosition(float p_angle)
{
    //Works
    float radius = (m_size.x * 0.5f);
    float alpha = (float)(((-m_rotation - p_angle) * DEGREES_TO_RADIANS) - 1.57);
    float ballPosx = -cos(alpha) * radius;
    float ballPosy = sin(alpha) * radius;
    float tempx = m_position.x + ballPosx;
    float tempy = m_position.y + ballPosy;

    return float2(tempx, tempy);
}

bool BOPaddle::GetStickyState()const
{
    return m_isSticky;
}

void BOPaddle::SetStickyState(bool p_active)
{
    m_isSticky = p_active;
}