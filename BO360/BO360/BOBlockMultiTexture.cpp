#include "BOBlockMultiTexture.h"


BOBlockMultiTexture::BOBlockMultiTexture()
{
	m_currentTextureIndex = -1;
}


BOBlockMultiTexture::~BOBlockMultiTexture()
{
}

bool BOBlockMultiTexture::AddTextureForHPAbove(std::string p_filename, int p_hp)
{
	SDL_Texture* newTexture = BOGraphicInterface::LoadTexture(p_filename);
	if (newTexture == NULL)
	{
		std::cout << "Unable to load " << p_filename << std::endl;
		return false;
	}

	// Only add if the new hp limit is above the last one
	int maxIndex = m_hpLimits.size() - 1;
	if (maxIndex >= 0 && p_hp <= m_hpLimits[maxIndex])
	{
		std::cout << "Unable to add new Texture to BOBlockMultiTexture: " << std::endl;
		std::cout << "New hp limit must be higher than previous hp limit." << std::endl;
		return false;
	}

	m_hpLimits.push_back(p_hp);
	m_textures.push_back(newTexture);

	// Raise the current texture index if our hp is above the new limit
	if (m_hp > m_hpLimits.back())
	{
		m_currentTextureIndex = m_hpLimits.size() - 1;
	}
}

void BOBlockMultiTexture::Draw()
{
	// If we're not using the texture array, draw our normal sprite
	if (m_currentTextureIndex < 0)
	{
		BOGraphicInterface::Draw(m_sprite, m_position, m_size);
	}
	else
	{
		BOGraphicInterface::Draw(m_textures[m_currentTextureIndex], m_position, m_size);
	}
	
}

bool BOBlockMultiTexture::Hit(int p_damage)
{
	int result = BOBlock::Hit(p_damage);

	// Drop to lower hp texture if we pass a limit
	while (m_currentTextureIndex >= 0 && m_hp <= m_hpLimits[m_currentTextureIndex])
	{
		m_currentTextureIndex--;
	}

	return result;
}