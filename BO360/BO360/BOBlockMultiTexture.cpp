#include "BOBlockMultiTexture.h"

BOBlockMultiTexture::BOBlockMultiTexture()
{
    m_damage = 0;
}

BOBlockMultiTexture::~BOBlockMultiTexture()
{

}

bool BOBlockMultiTexture::Hit(int p_damage)
{
	bool result = BOBlock::Hit(p_damage);

    m_damage += p_damage;
    if (m_damage > m_numberOfFrames)
	{
        m_damage = m_numberOfFrames;
	}

    SetFrame(m_damage);

	return result;
}