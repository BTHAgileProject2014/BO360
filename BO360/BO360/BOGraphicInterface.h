#ifndef BOGRAPHICINTERFACE_H_
#define BOGRAPHICINTERFACE_H_

#include "BOUtility.h"
#include "BOWindow.h"
#include "BOComponent.h"
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>

class BOGraphicInterface
{
public:
	~BOGraphicInterface();

	static bool Initialize();
	static bool Initialize(int p_windowWidth, int p_windowHeight);

	static void Shutdown();
	static void Draw(SDL_Texture* p_texture, float2 p_position, int2 p_size, int4 p_target, Uint8 p_opacity);
	static void Draw(SDL_Texture* p_texture, struct float2 p_position, struct int2 p_size, Uint8 p_opacity);
	static void DrawEx(SDL_Texture* p_texture, int4 p_source, int4 p_destination, double p_rotation, int2 p_rotationSource, Uint8 p_opacity);

	static void Clear();
	static void Present();

	static int2 GetWindowSize();
	static void SetWindowTitle(std::string p_windowText);

	static SDL_Texture* LoadTexture(std::string p_path);
	static SDL_Texture* DrawTextToTexture(std::string p_text, int3 p_textColor, int2* size, int p_fontSize, int p_maxWidth);
	static void DestroyTexture(SDL_Texture* p_texture);
    static void Offset(float2 p_offset);
    static void SetOffset(float2 p_offset);

private:
	BOGraphicInterface() {};
	static BOGraphicInterface& GetInstance();

	BOWindow m_window;
	static SDL_Renderer* m_renderer;
	int m_windowWidth;
	int m_windowHeight;
    float2 m_offset;

	//bool m_fullscreen;	// Use only when fullscreen and resolutions is supported
};
#endif

