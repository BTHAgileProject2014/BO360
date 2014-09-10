#include "BOGraphicInterface.h"

BOGraphicInterface::~BOGraphicInterface()
{
}

bool BOGraphicInterface::Initialize()
{
	BOGraphicInterface* selfPtr = &GetInstance();
	bool result;
	GetInstance().m_windowWidth = 800;
	GetInstance().m_windowHeight = 600;

	result = GetInstance().m_window.Initialize("ScreenName", GetInstance().m_windowWidth, GetInstance().m_windowHeight);
	if (!result)
	{
		// Initialize failed
		return false;
	}

	// Create and prepare the renderer
	GetInstance().m_renderer = SDL_CreateRenderer(GetInstance().m_window.GetUnderlyingSDLWindow(), -1, SDL_RENDERER_ACCELERATED);
	if (GetInstance().m_renderer == NULL)
	{
		// Failed to create renderer
		return false;
	}
	SDL_SetRenderDrawColor(GetInstance().m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	return true;
}

void BOGraphicInterface::Shutdown()
{
	GetInstance().m_window.Shutdown();
}
void BOGraphicInterface::Draw(SDL_Texture* p_texture, float2 p_position, int2 p_size)
{
	SDL_Rect rect;
	rect.x = (int)p_position.x;
	rect.y = (int)p_position.y;
	rect.w = p_size.x;
	rect.h = p_size.y;

	SDL_RenderCopy(GetInstance().m_renderer, p_texture, &rect, &rect);
}

void BOGraphicInterface::Clear()
{
	SDL_RenderClear(GetInstance().m_renderer);
}

void BOGraphicInterface::Present()
{
	SDL_RenderPresent(GetInstance().m_renderer);
}

SDL_Texture* BOGraphicInterface::LoadTexture(std::string p_path)
{
	SDL_Texture* newTexture = 0;

	// Apparently, we need to load to a surface first
	SDL_Surface* surface = SDL_LoadBMP(p_path.c_str());
	if (surface == NULL)
	{
		std::cout << "Failed to load image: " + p_path;
		// Failed to load! 
		// This should be handled
	}
	else
	{
		// Convert surface to SDL_Texture
		BOGraphicInterface* test = &GetInstance();
		SDL_Renderer* r = GetInstance().m_renderer;
		newTexture = SDL_CreateTextureFromSurface(GetInstance().m_renderer, surface);


		// Free the surface we loaded
		SDL_FreeSurface(surface);
	}

	return newTexture;
}

BOGraphicInterface& BOGraphicInterface::GetInstance()
{
	static BOGraphicInterface instance;
	return instance;
}