#include "BOBlackHole.h"

BOBlackHole::BOBlackHole()
{

}

BOBlackHole::~BOBlackHole()
{

}

void BOBlackHole::Update(double p_rotation)
{
    m_rotation += p_rotation;

    if (m_rotation > 360)
    {
        m_rotation -= 360;
    }
}

void BOBlackHole::DrawRotating()
{
    int4 source = int4(0, 0, m_size.x, m_size.y);
    int4 dest = int4((int)(m_position.x - m_scale * (m_size.x / 2)), (int)(m_position.y - m_scale * (m_size.y / 2)), (int)(m_scale * m_size.x), (int)(m_scale * m_size.y));
    BOGraphicInterface::DrawEx(m_sprite, source, dest, -m_rotation, int2(100, 100));
}