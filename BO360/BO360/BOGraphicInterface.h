#ifndef BOGRAPHICINTERFACE_H_
#define BOGRAPHICINTERFACE_H_

#include "BOUtility.h"
#include "BOWindow.h"
#include "BOComponent.h"
#include <iostream>
#include <SDL_image.h>

class BOGraphicInterface
{
public:
	~BOGraphicInterface();

	static bool Initialize();
	static bool Initialize(int p_windowWidth, int p_windowHeight);

	static void Shutdown();
	static void Draw(SDL_Texture* p_texture, float2 p_position, int2 p_size, int4 p_target);
	static void Draw(SDL_Texture* p_texture, struct float2 p_position, struct int2 p_size);
	static void DrawEx(SDL_Texture* p_texture, int4 p_source, int4 p_destination, double p_rotation, int2 p_rotationSource);
	static void Clear();
	static void Present();
	static void SetWindowTitle(std::string p_windowText);
	static SDL_Texture* LoadTexture(std::string p_path);

private:
	BOGraphicInterface() {}
	static BOGraphicInterface& GetInstance();

	BOWindow m_window;
	SDL_Renderer* m_renderer;
	int m_windowWidth;
	int m_windowHeight;
	//bool m_fullscreen;	// Use only when fullscreen and resolutions is supported
	
};
#endif

