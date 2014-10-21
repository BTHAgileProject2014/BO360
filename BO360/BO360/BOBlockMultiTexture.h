#ifndef BOBLOCKMULTITEXTURE_H_
#define BOBLOCKMULTITEXTURE_H_

#include "BOBlock.h"
#include <vector>

class BOBlockMultiTexture : public BOBlock
{
public:
	BOBlockMultiTexture();
	~BOBlockMultiTexture();

	bool Hit(int p_damage);
    void Revive();

private:
	std::vector<SDL_Texture*> m_textures;
    int m_damage;
};
#endif