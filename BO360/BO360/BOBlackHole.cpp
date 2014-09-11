#include "BOBlackHole.h"

BOBlackHole::BOBlackHole()
{
}

BOBlackHole::~BOBlackHole()
{
}

void BOBlackHole::Update()
{

	// Fix spinning hole and so on if wanted.
}

sphere BOBlackHole::GetBoundingSphere()
{
	return sphere(m_position, (m_size.x / 2));
}