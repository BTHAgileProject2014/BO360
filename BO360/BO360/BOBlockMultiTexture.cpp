#include "BOBlockMultiTexture.h"


BOBlockMultiTexture::BOBlockMultiTexture()
{
	m_currentTextureIndex = -1;
}


BOBlockMultiTexture::~BOBlockMultiTexture()
{
}

void BOBlockMultiTexture::Shutdown()
{
	// delete objects in array
	for (unsigned int i = 0; i < m_textures.size(); i++)
	{
		BOGraphicInterface::DestroyTexture(m_textures[i]);
	}

	m_textures.clear();
	m_textures.shrink_to_fit();
	// clear m_textures reallocating
	//std::vector<SDL_Texture*>().swap(m_textures);

	// clear m_hpLimits reallocating
	m_hpLimits.clear();
	m_hpLimits.shrink_to_fit();
	//std::vector<int>().swap(m_hpLimits);

	// clear array
	BOObject::Shutdown();
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

	return true;
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
	bool result = BOBlock::Hit(p_damage);

	// Drop to lower hp texture if we pass a limit
	while (m_currentTextureIndex >= 0 && m_hp <= m_hpLimits[m_currentTextureIndex])
	{
		m_currentTextureIndex--;
	}

	return result;
}