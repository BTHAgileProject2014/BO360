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

}