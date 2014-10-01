#ifndef _BOTEXTUREMANAGER_H_
#define _BOTEXTUREMANAGER_H_

#include <vector>
#include <SDL.h>
#include "BOUtility.h">

class BOTextureManager
{
public:
	~BOTextureManager();
	static BOTextureManager& GetInstance();
	static bool Initialize();
	static void Shutdown();

	static void LoadTexture();
	static void FreeTexture(int i);
	static void FreeAll();
private:
	BOTextureManager(){};
	BOTextureManager(BOTextureManager const &);
	void operator=(BOTextureManager const&);

private:
	static std::vector<SDL_Texture*> textureList;

};

#endif // !_BOTEXTUREMANAGER_H_
