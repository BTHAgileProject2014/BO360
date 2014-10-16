#include "BOObject.h"

BOObject::BOObject()
{
	m_sprite = NULL;
}

BOObject::~BOObject()
{

}

// Variable initilaize.
bool BOObject::Initialize(float2 p_position, int2 p_size, float p_scale, SDL_Texture* p_sprite)
{
	// Set variables.
	m_position = p_position;
	m_scale = p_scale;
    m_rotation = 0.0;
	SetSize(p_size);
    m_opacity = 255;

	// Load texture.
	m_sprite = p_sprite;

	return true;
}

// Variable initilaize.
bool BOObject::Initialize(float2 p_position, int2 p_size, SDL_Texture* p_sprite)
{
    return Initialize(p_position, p_size, 1, p_sprite);
}

// Shutdown and memory release.
void BOObject::Shutdown()
{

}

// Sprite Draw call.
void BOObject::Draw()
{
	int4 source = int4(0, 0, m_size.x, m_size.y);
	int4 dest = int4((int)(m_position.x - (m_scale * (m_size.x / 2))), (int)(m_position.y - (m_scale * (m_size.y / 2))), (int)(m_scale * m_size.x), (int)(m_scale * m_size.y));
    BOGraphicInterface::DrawEx(m_sprite, source, dest, m_rotation, int2(0, 0), m_opacity);
}

// Position Get / Set functions.
float2 BOObject::GetPosition() const
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
    return int2((int)(m_size.x * m_scale), (int)(m_size.y * m_scale));
}

void BOObject::SetSize(int2 p_size)
{
	m_size = p_size;
	m_radius = (p_size.x > p_size.y) ? m_scale * (p_size.x / 2.0f) : m_scale * (p_size.y / 2.0f);
}

// Sprite Get / Set functions.
SDL_Texture* BOObject::GetSprite()
{
	return m_sprite;
}

void BOObject::SetSprite(Textures p_spriteIndex)
{
	// Load new texture.
	m_sprite = BOTextureManager::GetTexture(p_spriteIndex);
}

sphere BOObject::GetBoundingSphere() const
{
	return sphere(m_position, m_radius);
}

double BOObject::GetRotation()
{
    return m_rotation;
}

void BOObject::SetRotation(double p_rotation)
{
    m_rotation = p_rotation;
}

Uint8 BOObject::GetOpacity()const
{
    return m_opacity;
}

void BOObject::SetOpacity(Uint8 p_opacity)
{
    m_opacity = p_opacity;
}

void BOObject::SetScale(float p_scale)
{
	m_scale = p_scale;
	m_radius = m_radius * (m_scale / 2);
}