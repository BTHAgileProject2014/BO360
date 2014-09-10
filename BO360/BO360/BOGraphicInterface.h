#ifndef BOGRAPHICINTERFACE_H_
#define BOGRAPHICINTERFACE_H_

#include "BOUtility.h"
#include "BOWindow.h"
#include "BOComponent.h"
#include <iostream>
#include "BOBlackHole.h"

class BOGraphicInterface
{
public:
	~BOGraphicInterface();

	static bool Initialize();
	static void Shutdown();
	static void Draw(SDL_Texture* p_texture, struct float2 p_position, struct int2 p_size);
	static void Clear();
	static void Present();
	static SDL_Texture* LoadTexture(std::string p_path);

private:
	BOGraphicInterface() {}
	static BOGraphicInterface& GetInstance();

	BOWindow m_window;
	SDL_Renderer* m_renderer;
	int m_windowWidth;
	int m_windowHeight;
	//bool m_fullscreen;	// Use only when fullscreen and resolutions is supported

	BOBlackHole* m_blackHole;
};
#endif

