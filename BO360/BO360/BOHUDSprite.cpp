#include "BOHUDSprite.h"


BOHUDSprite::BOHUDSprite()
{
}


BOHUDSprite::~BOHUDSprite()
{
}

bool BOHUDSprite::Initialize(float2 p_position, HUDAnchor p_anchor, int2 p_size, SDL_Texture* p_sprite)
{
    if (!m_sprite.Initialize(p_position, p_size, p_sprite))
    {
        std::cout << "Failed to initialize m_sprite in BOHUDSprite!" << std::endl;
        return false;
    }

    if (!BOHUDElement::Initialize(p_position, p_size, p_anchor))
    {
        std::cout << "Failed to initialize BOHUDElement in BOHUDSprite!" << std::endl;
        return false;
    }

    m_sprite.SetPosition(m_relativePosition);

    return true;
}

void BOHUDSprite::Shutdown()
{
    m_sprite.Shutdown();

    BOHUDElement::Shutdown();
}

void BOHUDSprite::Draw()
{
    if (m_enabled)
    {
        m_sprite.Draw();
    }
}

void BOHUDSprite::SetRelativePosition(HUDAnchor p_anchor)
{
    BOHUDElement::SetRelativePosition(p_anchor);
    m_sprite.SetPosition(m_relativePosition);
}

void BOHUDSprite::SetPosition(float2 p_position)
{
    m_position = p_position;
    SetRelativePosition(m_anchor);
}

