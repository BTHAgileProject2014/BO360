#include "BOTextureManager.h"
#include "BOGraphicInterface.h"

BOTextureManager::~BOTextureManager()
{
}

BOTextureManager& BOTextureManager::GetInstance()
{
	static BOTextureManager instance;
	return instance;
}

bool BOTextureManager::Initialize(std::string p_theme)
{
	// Initialize all textures we use.
    LoadTexture(p_theme);

	return true;
}

void BOTextureManager::Shutdown()
{
	FreeAll();
	std::vector<SDL_Texture*>().swap(GetInstance().textureList);
}

void BOTextureManager::LoadTexture(std::string p_theme)
{
	SDL_Texture* texture;

	// Balls.
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/placeholderBoll10x10.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/placeholderBoll2.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/placeholderBollFire.png");
	GetInstance().textureList.push_back(texture);

	// Hexagons, loaded using the theme.
    const std::string theme = "Sprites/Themes/" + p_theme;
    std::string filename;

    filename = theme + "/Blocks/BlockRegular.png";
    texture = BOGraphicInterface::LoadTexture(filename);
	GetInstance().textureList.push_back(texture);

    filename = theme + "/Blocks/BlockArmored.png";
    texture = BOGraphicInterface::LoadTexture(filename);
	GetInstance().textureList.push_back(texture);

    filename = theme + "/Blocks/BlockIndestructible.png";
    texture = BOGraphicInterface::LoadTexture(filename);
	GetInstance().textureList.push_back(texture);

    // Glows, loaded using the theme.
    filename = theme + "/Glows/GlowRegular.png";
    texture = BOGraphicInterface::LoadTexture(filename);
	GetInstance().textureList.push_back(texture);

    filename = theme + "/Glows/GlowArmored.png";
    texture = BOGraphicInterface::LoadTexture(filename);
	GetInstance().textureList.push_back(texture);

    filename = theme + "/Glows/GlowIndestructible.png";
    texture = BOGraphicInterface::LoadTexture(filename);
	GetInstance().textureList.push_back(texture);

	// Hexagon with powerups.
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagonPU1.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagonPU2.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagonPU3.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagonPU4.png");
	GetInstance().textureList.push_back(texture); 
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagonPUShockwave.png");
    GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagonPU.png");
	GetInstance().textureList.push_back(texture);

	// Powerups.
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderSheild.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderPowerupMultBall.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderPowerup4.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderPowerup2.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderPowerup3.png");
	GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderPowerupShockwave.png");
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderSlowTime.png");
    GetInstance().textureList.push_back(texture);
	// Particles
	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/BallTrail.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/BallDebris.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/BlockDebris.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/PowerUpDebris.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/Explosion.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/DebugTrail.png");
	GetInstance().textureList.push_back(texture);

	// HUD.
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/placeholderLife.png");
	GetInstance().textureList.push_back(texture);

	// Menu.
	texture = BOGraphicInterface::LoadTexture("Sprites/Menu/MenuEdge.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Menu/MenuBar.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Menu/MainMenuBackground.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Menu/Button.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Menu/ButtonHighlighted.png");
	GetInstance().textureList.push_back(texture);

	// Misc.
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Background.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/placeholderBlackhole110x110.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/placeholderPadSegment5.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Menu/ButtonToolTip.png");
	GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/placeholderHyperdrive.png");
    GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/placeholderLock.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/DEBUGDIR.png");
	GetInstance().textureList.push_back(texture);

	GetInstance().textureList.push_back(NULL);// Lägg in en tom för att fixa nrOfLevels
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/button1Map.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/button2Map.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/buttonDefaultMap.png");
	GetInstance().textureList.push_back(texture);
}

void BOTextureManager::FreeTexture(int p_textureIndex)
{
	BOGraphicInterface::DestroyTexture(GetInstance().textureList[p_textureIndex]);
}

void BOTextureManager::FreeAll()
{
	for (unsigned int i = 0; i < GetInstance().textureList.size(); i++)
	{
		BOGraphicInterface::DestroyTexture(GetInstance().textureList[i]);
	}
	
}

SDL_Texture* BOTextureManager::GetTexture(Textures p_textureEnum)
{
	return GetInstance().textureList[p_textureEnum];
}

SDL_Texture* BOTextureManager::GetTextureInt(int p_textureEnumIndex)
{
	return GetInstance().textureList[p_textureEnumIndex];
}
