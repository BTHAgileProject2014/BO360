#include "BOHUDElement.h"


BOHUDElement::BOHUDElement()
{
}


BOHUDElement::~BOHUDElement()
{
}

bool BOHUDElement::Initialize(float2 p_position, int2 p_size, HUDAnchor p_anchor)
{
    m_position = p_position;
    m_anchor = p_anchor;
    m_size = p_size;
    m_enabled = true;

    SetRelativePosition(m_anchor);
    return true;
}

void BOHUDElement::Shutdown()
{

}

void BOHUDElement::SetRelativePosition(HUDAnchor p_anchor)
{
    switch (m_anchor)
    {
        case HUDANCHOR_CENTER:
            m_relativePosition = m_position;
            break;
        case HUDANCHOR_TOP:
            m_relativePosition = float2(m_position.x, m_position.y - m_size.y * 0.5f);
            break;
        case HUDANCHOR_LEFT:
            m_relativePosition = float2(m_position.x - m_size.x * 0.5f, m_position.y);
            break;
        case HUDANCHOR_BOTTOM:
            m_relativePosition = float2(m_position.x, m_position.y + m_size.y * 0.5f);
            break;
        case HUDANCHOR_RIGHT:
            m_relativePosition = float2(m_position.x + m_size.x * 0.5f, m_position.y);
            break;
        case HUDANCHOR_TOPLEFT:
            m_relativePosition = float2(m_position.x - m_size.x * 0.5f, m_position.y - m_size.y * 0.5f);
            break;
        case HUDANCHOR_TOPRIGHT:
            m_relativePosition = float2(m_position.x + m_size.x * 0.5f, m_position.y - m_size.y * 0.5f);
            break;
        case HUDANCHOR_BOTTOMLEFT:
            m_relativePosition = float2(m_position.x - m_size.x * 0.5f, m_position.y + m_size.y * 0.5f);
            break;
        case HUDANCHOR_BOTTOMRIGHT:
            m_relativePosition = float2(m_position.x + m_size.x * 0.5f, m_position.y + m_size.y * 0.5f);
            break;
    }
}

void BOHUDElement::EnableElement(bool p_enable)
{
    m_enabled = p_enable;
}

int2 BOHUDElement::GetSize()const
{
    return m_size;
}

void BOHUDElement::SetPosition(float2 p_position)
{
    m_position = p_position;
    SetRelativePosition(m_anchor);
}

float2 BOHUDElement::GetPosition()const
{
    return m_position;
}
