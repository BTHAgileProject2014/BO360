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
	return BOObject::Initialize(p_position, p_size, p_fileName);
}

void BOPaddle::Handle(InputMessages p_inputMessages)
{

}

void BOPaddle::Update()
{
}

void BOPaddle::Draw()
{
	int4 mySource = int4(0, 0, m_size.x, m_size.y);
	int4 myDest = int4((int)m_position.x - (m_size.x / 2), (int)m_position.y - (m_size.y / 2), m_size.x, m_size.y);
	BOGraphicInterface::DrawEx(m_sprite, mySource, myDest, m_rotation, int2(m_size.x / 2, m_size.y / 2));
}