#include "BOHUDText.h"


BOHUDText::BOHUDText()
{
}


BOHUDText::~BOHUDText()
{
}

bool BOHUDText::Initialize(float2 p_position, HUDAnchor p_anchor, std::string p_text, int3 p_color, int p_fontSize, int p_maxWidth)
{
    bool result = false;

    result = m_text.Initialize(float2(0, 0), p_text, p_color, p_fontSize, p_maxWidth);
    if (!result)
    {
        std::cout << "Failed to initialize BODrawableText in BOHUDText!" << std::endl;
        return false;
    }

    result = BOHUDElement::Initialize(p_position, m_text.GetSize(), p_anchor);
    if (!result)
    {
        std::cout << "Failed to initialize BOHUDElement in BOHUDText!" << std::endl;
        return false;
    }

    m_text.SetPosition(m_relativePosition);

    return true;
}

void BOHUDText::Shutdown()
{
    m_text.Shutdown();
    BOHUDElement::Shutdown();
}

void BOHUDText::Draw()
{
    if (m_enabled)
    {
        m_text.Draw();
    }
}

void BOHUDText::SetText(std::string p_text, int3 p_color, int p_maxWidth)
{
    m_text.SetText(p_text, p_color, p_maxWidth);
    SetRelativePosition(m_anchor);
    m_text.SetPosition(m_relativePosition);
}

void BOHUDText::SetPosition(float2 p_position)
{
    BOHUDElement::SetPosition(p_position);
    m_text.SetPosition(m_relativePosition);
}


