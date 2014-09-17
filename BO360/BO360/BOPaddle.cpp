#include "BOPaddle.h"


BOPaddle::BOPaddle()
{
}


BOPaddle::~BOPaddle()
{
}

bool BOPaddle::Initialize(float2 p_position, int2 p_size, std::string p_fileName)
{
	m_rotation = 0.0f;
	m_deltaRotation = 0.4f;
	BOPublisher::AddSubscriber(this);
	return BOObject::Initialize(p_position, p_size, p_fileName);
	
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
}

void BOPaddle::Update()
{
	if (m_movingLeft)
	{
		m_rotation -= m_deltaRotation;
		if (m_rotation < 0)
		{
			m_rotation += 360;
		}
	}
	else if (m_movingRight)
	{
		m_rotation += m_deltaRotation;
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
	BOGraphicInterface::DrawEx(m_sprite, mySource, myDest, m_rotation, int2(m_size.x / 2, m_size.y / 2));
}

double BOPaddle::GetRotation()
{
	return m_rotation;
}