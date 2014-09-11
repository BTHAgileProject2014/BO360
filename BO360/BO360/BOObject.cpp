#include "BOObject.h"

// Constructor / Destructor.
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
	m_size = p_size;

	// Load texture.
	m_sprite = BOGraphicInterface::LoadTexture(p_fileName);

	return true;
}

// Shutdown and memory release.
void BOObject::Shutdown()
{

}

// Sprite Draw call.
void BOObject::Draw()
{
	BOGraphicInterface::Draw(m_sprite, m_position, m_size);
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
	int largestSize = (m_size.x > m_size.y ? m_size.x : m_size.y);
	return sphere(m_position, largestSize / 2);
}