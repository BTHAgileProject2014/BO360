#include "BOHUDActionBar.h"


BOHUDActionBar::BOHUDActionBar()
{
}


BOHUDActionBar::~BOHUDActionBar()
{
}

bool BOHUDActionBar::Initialize(float2 p_position)
{

    m_actionBarButtons[0].Initialize(p_position - float2(150, 0), BOTextureManager::GetTexture(TEXPUSHOCKWAVE), int2(40, 40), "F");  // Shockwave
    m_actionBarButtons[1].Initialize(p_position - float2(90, 0), BOTextureManager::GetTexture(TEXPUSHOCKWAVE), int2(40, 40), "DOWN");  // Slow Time
    m_actionBarButtons[2].Initialize(p_position - float2(30, 0), BOTextureManager::GetTexture(TEXPUSHOCKWAVE), int2(40, 40), "XD");  // Slow Time
    m_actionBarButtons[3].Initialize(p_position - float2(-30, 0), BOTextureManager::GetTexture(TEXPUSHOCKWAVE), int2(40, 40), "XD");  // Slow Time
    m_actionBarButtons[4].Initialize(p_position - float2(-90, 0), BOTextureManager::GetTexture(TEXPUSHOCKWAVE), int2(40, 40), "XD");  // Slow Time
    m_actionBarButtons[5].Initialize(p_position - float2(-150, 0), BOTextureManager::GetTexture(TEXPUSHOCKWAVE), int2(40, 40), "XD");  // Slow Time
    return true;
}

void BOHUDActionBar::Shutdown()
{
    for (int i = 0; i < 6; i++)
    {
        m_actionBarButtons[i].Shutdown();
    }
}

void BOHUDActionBar::Draw()
{
    // Draw Buttons
    for (int i = 0; i < 6; i++)
    {
        m_actionBarButtons[i].Draw();
    }
}
