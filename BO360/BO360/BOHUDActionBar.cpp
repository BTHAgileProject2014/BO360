#include "BOHUDActionBar.h"


BOHUDActionBar::BOHUDActionBar()
{
}


BOHUDActionBar::~BOHUDActionBar()
{
}

bool BOHUDActionBar::Initialize(float2 p_position)
{

    m_actionBarButtons[0].Initialize(p_position - float2(100, 0), BOTextureManager::GetTexture(TEXPUSHOCKWAVE), int2(40, 40), "DOWN");  //Shockwave

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
