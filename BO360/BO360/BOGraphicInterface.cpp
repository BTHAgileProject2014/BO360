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


	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "Failed to init SDL_Image:" << IMG_GetError() << std::endl;
		return false;
	}

	return true;
}

void BOGraphicInterface::Shutdown()
{
	GetInstance().m_window.Shutdown();
}
void BOGraphicInterface::Draw(SDL_Texture* p_texture, float2 p_position, int2 p_size)
{
	SDL_Rect source, target;
	target.x = (int)p_position.x;
	target.y = (int)p_position.y;
	target.w = p_size.x;
	target.h = p_size.y;
	source.x = 0;
	source.y = 0;
	source.w = p_size.x;
	source.h = p_size.y;

	SDL_RenderCopy(GetInstance().m_renderer, p_texture, &source, &target);
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
	SDL_Surface* surface = IMG_Load(p_path.c_str());
	if (surface == NULL)
	{
		std::cout << "Failed to load image: " + p_path << std::endl;
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