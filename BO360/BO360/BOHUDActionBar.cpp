#include "BOHUDActionBar.h"


BOHUDActionBar::BOHUDActionBar()
{
}


BOHUDActionBar::~BOHUDActionBar()
{
}

bool BOHUDActionBar::Initialize(float2 p_position)
{
    // Initialize Buttons with their respective texture and hotkey
    m_actionBarButtons[ABB_SLOWTIME].Initialize(p_position - float2(120, 0), BOTextureManager::GetTexture(TEXPUSLOWTIME), int2(40, 40), "DOWN");
    m_actionBarButtons[ABB_SHOCKWAVE].Initialize(p_position - float2(60, 0), BOTextureManager::GetTexture(TEXPUSHOCKWAVE), int2(40, 40), "F");
    m_actionBarButtons[ABB_MEGAPAD].Initialize(p_position - float2(0, 0), BOTextureManager::GetTexture(TEXHUDMEGAPAD), int2(40, 40), "G");
    m_actionBarButtons[ABB_GIANTBALL].Initialize(p_position - float2(-60, 0), BOTextureManager::GetTexture(TEXHUDGIANTBALL), int2(40, 40), "H");
    m_actionBarButtons[ABB_QUANTUMFUEL].Initialize(p_position - float2(-120, 0), BOTextureManager::GetTexture(TEXHUDQUANTUMFUEL), int2(40, 40), "J");

    return true;
}

void BOHUDActionBar::Shutdown()
{
    for (int i = 0; i < ABB_NROFBUTTONS; i++)
    {
        m_actionBarButtons[i].Shutdown();
    }
}

void BOHUDActionBar::Draw()
{
    // Draw Buttons
    for (int i = 0; i < ABB_NROFBUTTONS; i++)
    {
        m_actionBarButtons[i].Draw();
    }
}

void BOHUDActionBar::Enable(bool p_enabled, ActionBarButton p_button)
{
    m_actionBarButtons[p_button].SetEnabled(p_enabled);
}

void BOHUDActionBar::CanUse(bool p_canUse, ActionBarButton p_button)
{
    m_actionBarButtons[p_button].CanUse(p_canUse);
}