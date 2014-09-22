#include "BOGraphicInterface.h"

SDL_Renderer* BOGraphicInterface::m_renderer;

BOGraphicInterface::~BOGraphicInterface()
{
}

bool BOGraphicInterface::Initialize()
{
	return Initialize(800, 600);
}

bool BOGraphicInterface::Initialize(int p_windowWidth, int p_windowHeight)
{
	bool result;
	GetInstance().m_windowWidth = p_windowWidth;
	GetInstance().m_windowHeight = p_windowHeight;

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

	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << "\n";
		return false;
	}

	return true;
}

void BOGraphicInterface::Shutdown()
{
	GetInstance().m_window.Shutdown();

	// Free up the TTF library
	TTF_Quit();
}



void BOGraphicInterface::DrawEx(SDL_Texture* p_texture, int4 p_source, int4 p_destination, double p_rotation, int2 p_rotationSource)
{
	SDL_Rect source;
	source.x = p_source.x;
	source.y = p_source.y;
	source.w = p_source.z;
	source.h = p_source.w;

	SDL_Rect destionation;
	destionation.x = p_destination.x;
	destionation.y = p_destination.y;
	destionation.w = p_destination.z;
	destionation.h = p_destination.w;

	SDL_Point rotationSource;
	rotationSource.x = p_rotationSource.x;
	rotationSource.y = p_rotationSource.y;

	SDL_RenderCopyEx(GetInstance().m_renderer, p_texture, &source, &destionation, p_rotation, &rotationSource, SDL_FLIP_NONE);
}

void BOGraphicInterface::Draw(SDL_Texture* p_texture, float2 p_position, int2 p_size, int4 p_source)
{
	SDL_Rect source, target;
	target.x = (int)p_position.x - (p_size.x / 2);
	target.y = (int)p_position.y - (p_size.y / 2);
	target.w = p_size.x;
	target.h = p_size.y;
	source.x = p_source.x;
	source.y = p_source.y;
	source.w = p_source.z;
	source.h = p_source.w;
	
	 
	// Prototype rotation
	//SDL_Point p;
	//p.x = p_size.x / 2;
	//p.y = p_size.y / 2;
	//double angle = 0;
	//if (p_size.y == 80)
	//{
	//	static double specialAngle = 0.0f;
	//	specialAngle += 0.05f;
	//	angle = specialAngle;
	//}
	//SDL_RenderCopyEx(GetInstance().m_renderer, p_texture, &source, &target, angle, &p, SDL_FLIP_NONE);
	//

	SDL_RenderCopy(GetInstance().m_renderer, p_texture, &source, &target);
}
void BOGraphicInterface::Draw(SDL_Texture* p_texture, float2 p_position, int2 p_size)
{
	int4 source;
	source.x = 0;
	source.y = 0;
	source.z = p_size.x;
	source.w = p_size.y;

	Draw(p_texture, p_position, p_size, source);
}


void BOGraphicInterface::Clear()
{
	SDL_RenderClear(GetInstance().m_renderer);
}

void BOGraphicInterface::Present()
{
	SDL_RenderPresent(GetInstance().m_renderer);
}

void BOGraphicInterface::SetWindowTitle(std::string p_windowText)
{
	GetInstance().m_window.SetWindowText(p_windowText);
}

SDL_Texture* BOGraphicInterface::LoadTexture(std::string p_path)
{
	SDL_Texture* newTexture = 0;

	// Apparently, we need to load to a surface first
	SDL_Surface* surface = IMG_Load(p_path.c_str());
	if (surface == NULL)
	{
		std::cout << "Failed to load image: " + p_path << std::endl;
		std::cout << IMG_GetError() << std::endl;
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

SDL_Texture* BOGraphicInterface::DrawTextToTexture(std::string p_text, int3 p_textColor, int2* p_size, int p_fontSize)
{
	// Load the font
	TTF_Font* font = TTF_OpenFont("Font/Neon_Nanoborg.otf", p_fontSize);
	if (font == NULL)
	{
		std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << "\n";
		return false;
	}

	// The new texture
	SDL_Texture* texture;

	// Conversion
	SDL_Color textColor = { p_textColor.x, p_textColor.y, p_textColor.z, 255 };

	// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, p_text.c_str(), textColor);

	// Create texture from surface pixels
	texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

	//Get image dimensions
	p_size->x = textSurface->w;
	p_size->y = textSurface->h;

	// Get rid of the surface
	SDL_FreeSurface(textSurface);

	// Close Font
	TTF_CloseFont(font);

	return texture;
}

void BOGraphicInterface::DestroyTexture(SDL_Texture* p_texture)
{
	SDL_DestroyTexture(p_texture);
}

int2 BOGraphicInterface::GetWindowSize()
{
	return int2(GetInstance().m_windowWidth, GetInstance().m_windowHeight);
}