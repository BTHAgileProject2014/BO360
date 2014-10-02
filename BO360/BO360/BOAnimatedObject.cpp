#include "BOAnimatedObject.h"

BOAnimatedObject::BOAnimatedObject()
{

}

BOAnimatedObject::~BOAnimatedObject()
{

}

// Variable initilaize.
bool BOAnimatedObject::Initialize(float2 p_position, int2 p_size, int2 p_sourceSize, int p_frame, int p_numberOfFrames, double p_timePerFrame, bool p_hardReset, std::string p_fileName)
{
	m_sourceSize = p_sourceSize;
	m_frame = p_frame;
	m_numberOfFrames = p_numberOfFrames - 1;
	m_timePerFrame = p_timePerFrame;
	m_timePassed = 0;
	m_hardReset = p_hardReset;
	m_increment = true;

	m_position = p_position;
	m_size = p_size;
	m_sprite = BOGraphicInterface::LoadTexture(p_fileName);

	return true;
}

void BOAnimatedObject::Animate(double p_deltaTime)
{
	m_timePassed += p_deltaTime;

	if (m_timePassed > m_timePerFrame)
	{
		m_timePassed = 0;

		// Move frames forward if incrementing.
		if (m_increment)
		{
			m_frame++;

			if (m_frame > m_numberOfFrames)
			{
				// If we want to hard reset, move the frame back to 0.
				if (m_hardReset)
				{
					m_frame = 0;
				}

				// Else, start decrementing.
				else
				{
					m_frame = m_numberOfFrames - 1;
					m_increment = false;
				}
			}
		}

		// Move frames backwards if not incrementing.
		else
		{
			m_frame--;

			// Start incrementing again after 0.
			if (m_frame < 0)
			{
				m_frame = 1;
				m_increment = true;
			}
		}
	}
}

void BOAnimatedObject::MoveFrame(int p_frames)
{
	// Add p_frames, and keep it within the bounds.
	m_frame += p_frames;

	if (m_frame > m_numberOfFrames)
	{
		m_frame = m_numberOfFrames;
	}

	else if (m_frame < 0)
	{
		m_frame = 0;
	}
}

// Sprite Draw call.
void BOAnimatedObject::DrawAnimated()
{
	int4 l_target = int4((int)m_position.x - m_size.x / 2, (int)m_position.y - m_size.y / 2, m_size.x, m_size.y);
	int4 l_source = int4(m_sourceSize.x * m_frame, 0, m_sourceSize.x, m_sourceSize.y);

	BOGraphicInterface::DrawEx(m_sprite, l_source, l_target, 0.0, int2(l_source.z / 2, l_source.w / 2));
}

// Size Get / Set functions.
int2 BOAnimatedObject::GetSourceSize()
{
	return m_sourceSize;
}

void BOAnimatedObject::SetSourceSize(int2 p_sourceSize)
{
	m_sourceSize = p_sourceSize;
}

int BOAnimatedObject::GetFrame()
{
	return m_frame;
}

void BOAnimatedObject::SetFrame(int p_frame)
{
	m_frame = p_frame;

	if (m_frame > m_numberOfFrames)
	{
		m_frame = m_numberOfFrames;
	}

	else if (m_frame < 0)
	{
		m_frame = 0;
	}
}