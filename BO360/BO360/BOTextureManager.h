#ifndef _BOTEXTUREMANAGER_H_
#define _BOTEXTUREMANAGER_H_

#include <vector>
#include <SDL.h>
#include "BOUtility.h"

class BOTextureManager
{
public:
	~BOTextureManager();
	static BOTextureManager& GetInstance();
    static bool Initialize(std::string p_theme);
	static void Shutdown();

    static void LoadTexture(std::string p_theme);
	static void FreeTexture(int p_textureIndex);
	static void FreeAll();
	static SDL_Texture* GetTexture(Textures texturename);
	static SDL_Texture* GetTextureInt(int p_textureEnum);
private:
	BOTextureManager(){};
	BOTextureManager(BOTextureManager const &);
	void operator=(BOTextureManager const&);

private:
	std::vector<SDL_Texture*> textureList;

};

#endif // !_BOTEXTUREMANAGER_H_
