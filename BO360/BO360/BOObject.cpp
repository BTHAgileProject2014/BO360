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
	m_sprite = SDL_LoadBMP(p_fileName.c_str());

	return true;
}

// Shutdown and memory release.
void BOObject::Shutdown()
{
	// Delete the sprite.
	if (m_sprite)
	{
		delete m_sprite;
		m_sprite = NULL;
	}
}

// Sprite Draw call.
void BOObject::Draw()
{
	// TODO: add Draw call here.
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
SDL_Surface* BOObject::GetSprite()
{
	return m_sprite;
}

void BOObject::SetSprite(std::string p_fileName)
{
	// Delete the old sprite.
	if (m_sprite)
	{
		delete m_sprite;
		m_sprite = NULL;
	}

	// Load new texture.
	m_sprite = SDL_LoadBMP(p_fileName.c_str());
}