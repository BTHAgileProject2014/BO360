#include "BOKey.h"


BOKey::BOKey()
{
}


BOKey::~BOKey()
{
}

bool BOKey::Initialize(float2 p_position, int2 p_size, std::string p_fileName)
{
	if (!BOObject::Initialize(p_position, p_size, p_fileName))
	{
		return false;
	}

	return true;
}

void BOKey::Shutdown()
{
}

void BOKey::Update(double p_deltaTime)
{
}

void BOKey::Draw()
{
	BOObject::Draw();
}