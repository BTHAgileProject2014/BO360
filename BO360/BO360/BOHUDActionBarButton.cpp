#include "BOHUDActionBarButton.h"


BOHUDActionBarButton::BOHUDActionBarButton()
{
}


BOHUDActionBarButton::~BOHUDActionBarButton()
{
}

bool BOHUDActionBarButton::Initialize(float2 p_position, SDL_Texture* p_sprite, int2 p_size, std::string p_hotkey)
{
    m_enabled = true;
    m_button.Initialize(p_position, p_size, p_sprite);
    m_background.Initialize(p_position, p_size + int2(20,20), BOTextureManager::GetTexture(TEXACTIONBARBUTTONBG));

    m_buttonText.Initialize(float2(p_position.x, p_position.y - 30), p_hotkey, int3(255, 255, 255), 20, 0);

    return true;
}

void BOHUDActionBarButton::Shutdown()
{
    m_background.Shutdown();
    m_button.Shutdown();
    m_buttonText.Shutdown();
}

void BOHUDActionBarButton::Draw()
{
    // Draw button
    m_background.Draw();
    m_button.Draw();
    if (!m_enabled)
    {
        // Draw disabled overlay

    }
    m_buttonText.Draw();
}

void BOHUDActionBarButton::SetEnabled(bool p_enabled)
{
    m_enabled = p_enabled;
}
