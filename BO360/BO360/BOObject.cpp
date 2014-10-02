#include "BOObject.h"

BOObject::BOObject()
{
	m_sprite = NULL;
}

BOObject::~BOObject()
{

}

// Variable initilaize.
bool BOObject::Initialize(float2 p_position, int2 p_size, std::string p_fileName)
{
	// Set variables.
	m_position = p_position;
	SetSize(p_size);
	
	// Load texture.
	m_sprite = BOGraphicInterface::LoadTexture(p_fileName);

	return true;
}

// Shutdown and memory release.
void BOObject::Shutdown()
{
	if (m_sprite)
	{
		BOGraphicInterface::DestroyTexture(m_sprite);
	}
}

// Sprite Draw call.
void BOObject::Draw()
{
	int4 source = int4(0, 0, m_size.x, m_size.y);
	int4 dest = int4((int)m_position.x - m_size.x / 2, (int)m_position.y - m_size.y / 2, m_size.x, m_size.y);
	BOGraphicInterface::DrawEx(m_sprite, source, dest, 0, int2(0, 0));
}

// Position Get / Set functions.
float2 BOObject::GetPosition()
{
	return m_position;
}

void BOObject::SetPosition(float2 p_position)
{
	m_position = p_position;
}

// Size Get / Set functions.
int2 BOObject::GetSize()
{
	return m_size;
}

void BOObject::SetSize(int2 p_size)
{
	m_size = p_size;
	m_radius = (p_size.x > p_size.y) ? (float)p_size.x / 2.0f : (float)p_size.y / 2.0f;
}

// Sprite Get / Set functions.
SDL_Texture* BOObject::GetSprite()
{
	return m_sprite;
}

void BOObject::SetSprite(std::string p_fileName)
{
	// Load new texture.
	m_sprite = BOGraphicInterface::LoadTexture(p_fileName);
}

sphere BOObject::GetBoundingSphere()
{
	return sphere(m_position, m_radius);
}