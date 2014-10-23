#include "BOPaddle.h"

BOPaddle::BOPaddle()
{

}

BOPaddle::~BOPaddle()
{

}

bool BOPaddle::Initialize(float2 p_position, int2 p_size, int2 p_sourceSize, int p_frame, int p_numberOfFrames, double p_timePerFrame, bool p_hardReset, SDL_Texture* p_sprite)
{
    m_isSticky = false;
    m_isPrevSticky = false;
	m_rotation = 0.0;
	m_totalDegrees = 21.2;
	m_segementDegree = m_totalDegrees;
	m_segments = 1;
	m_minSegments = 1;
	m_maxSegments = 5 + BOTechTreeEffects::PaddleEffects.maxSize;
	AddSegments(3 + BOTechTreeEffects::PaddleEffects.size); // 2 here -> Start with total 3 segments
	m_deltaRotation = 200 * BOTechTreeEffects::PaddleEffects.speed;
    m_stickyMaxTimer = 0;
	SetStickyTimer(20);
    m_stickyCurrentTimer = 0;
	m_megaPadActive = false;
	m_megaPadTimeElapsed = 0;
	m_megaPadTimeDuration = 8.0;
	m_megaPadCoolDown = 0;
	BOPublisher::AddSubscriber(this);
	BOPowerUpManager::AddSubscriber(this);

    m_stickyGlow = BOTextureManager::GetTexture(TEXSTICKYPAD);
	
    return BOAnimatedObject::Initialize(p_position, p_size, p_sourceSize, p_frame, p_numberOfFrames, p_timePerFrame, p_hardReset, p_sprite);
}

void BOPaddle::Handle(InputMessages p_inputMessages)
{
    // Don't update paddle if a key is pressed while paused
    if (BOGlobals::GAME_STATE == PAUSED)
    {
        return;
    }

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
				if (m_segments < m_maxSegments)
				{
					AddSegments(1);
					int randomNr;
					randomNr = rand() % 100 + 1; // random nr from 1-100;
					if (randomNr <= (100 * BOTechTreeEffects::PUEffects.biggerPadEffectMultiplier))
					{
						AddSegments(1);
					}
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
				if (m_segments > m_minSegments)
				{
					RemoveSegments(1);
				}
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
    m_isPrevSticky = m_isSticky;

    // Move the pad left or right
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

    // Set a timeout for the sticky thing that sometimes is on the pad
    if (GetStickyState())
    {
        m_stickyCurrentTimer -= p_deltaTime;
        if (m_stickyCurrentTimer <= 0)
        {
            m_stickyCurrentTimer = 0;
            SetStickyState(false);
        }
    }
    
	if (m_megaPadActive)
	{
		//m_megaPadTimeElapsed += p_deltaTime * BOPhysics::GetTimeScale();
		if (m_megaPadTimeElapsed >= m_megaPadTimeDuration)
		{
			DeactivateMegaPad();
			m_megaPadTimeElapsed = 0;
		}
	}
	if (m_megaPadCoolDown > 0.0)
	{
		m_megaPadCoolDown -= p_deltaTime * BOPhysics::GetTimeScale();
	}
    else
    {
        BOHUDManager::ActionBarButtonCanUse(ABB_MEGAPAD, true);
    }
	
	// Animate the fire 
    BOAnimatedObject::Animate(p_deltaTime);
}

void BOPaddle::Draw()
{
    int4 target = int4((int)m_position.x - m_size.x / 2, (int)m_position.y - m_size.y / 2, m_size.x, m_size.y);
    int4 source = int4(m_sourceSize.x * m_frame, 0, m_sourceSize.x, m_sourceSize.y);

	for (int i = 0; i < m_segments; i++)
	{
        // If the pad is sticky, draw a glow around its edge.
        if (m_isSticky)
        {
            int4 stickyTarget = int4((int)m_position.x - (m_size.x + 8) / 2, (int)m_position.y - (m_size.y + 8) / 2, m_size.x + 8, m_size.x + 8);
            int4 stickySource = int4(0, 0, (m_size.x + 8), (m_size.y + 8));

            BOGraphicInterface::DrawEx(m_stickyGlow, stickySource, stickyTarget, m_rotation + ((double)m_segementDegree * i), int2(stickySource.z / 2, stickySource.w / 2), m_opacity);
        }

        BOGraphicInterface::DrawEx(m_sprite, source, target, m_rotation + ((double)m_segementDegree * i), int2(source.z / 2, source.w / 2), m_opacity);
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
	if ((m_segments+p_segments) <= m_maxSegments)
	{
		m_totalDegrees = m_totalDegrees + (m_segementDegree * p_segments);
		m_segments += p_segments;
	}
}

void BOPaddle::RemoveSegments(int p_segments)
{
	if ((m_segments-p_segments) >= m_minSegments)
	{
		m_totalDegrees = m_totalDegrees - (m_segementDegree * p_segments);
		m_segments -= p_segments;
	}
}

double BOPaddle::GetDegrees() const
{
	return m_totalDegrees + 8;
}

float2 BOPaddle::GetBallSpawnPosition()
{
    float radius = (m_size.x * 0.5f);
	float alpha = (float)((-m_rotation - (21.2f + (0.5f * 21.2f * (m_segments - 3.0f)))) * DEGREES_TO_RADIANS) - 1.57f;
	float ballPosx = -cos(alpha) * radius;
    float ballPosy = sin(alpha) * radius;
    float tempx = m_position.x + ballPosx;
	float tempy = m_position.y + ballPosy;

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
    m_stickyCurrentTimer = m_stickyMaxTimer;
}

void BOPaddle::SetStickyTimer(double p_time)
{
    m_stickyMaxTimer = p_time + BOTechTreeEffects::LevelEffects.stickyPadPUDuration;
}

double BOPaddle::GetStickyTimer() const
{
    return m_stickyMaxTimer;
}

void BOPaddle::ActivateMegaPad()
{
    if (BOTechTreeEffects::UtilityEffects.megaPadEnabled)
    {
        if (m_megaPadCoolDown <= 0)
        {
            int megapad = 17;
            m_preMegaSegments = m_segments;
            m_totalDegrees = (m_segementDegree * megapad);
            if (m_totalDegrees > 359)
            {
                m_totalDegrees = 359;
            }
            m_segments = megapad;


            m_megaPadActive = true;
            m_megaPadCoolDown = 20 * BOTechTreeEffects::PUEffects.decreaseCD;

            BOSoundManager::PlaySound(SOUND_BUMP);
        }
    }
}

void BOPaddle::DeactivateMegaPad()
{
	if (m_preMegaSegments != 0)
	{
		m_totalDegrees = (m_segementDegree * m_preMegaSegments);
		m_segments = m_preMegaSegments;

		m_megaPadActive = false;
	}
	
}

double BOPaddle::GetStickyTimeLeft() const
{
    return m_stickyCurrentTimer;
}

bool BOPaddle::StickyGotRemoved() const
{
    return (!m_isSticky && m_isPrevSticky);
}

void BOPaddle::UnsetStickyGotRemovedFlag()
{
    // This is bad bad bad
    // Do I care? No!
    // But seriously... This is a biproduct of the whole StickyGotRemoved() idea, so don't blame me!
    m_isPrevSticky = m_isSticky;
}