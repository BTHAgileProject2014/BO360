#pragma once
#include "BOBlock.h"
#include <vector>
class BOBlockMultiTexture :
	public BOBlock
{
public:
	BOBlockMultiTexture();
	~BOBlockMultiTexture();
	void Shutdown();
	bool AddTextureForHPAbove(std::string p_filename, int p_hp);
	void Draw();
	bool Hit(int p_damage);
private:
	std::vector<SDL_Texture*> m_textures;
	std::vector<int> m_hpLimits;
	int m_currentTextureIndex;
};

