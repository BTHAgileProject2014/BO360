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

bool BOTextureManager::Initialize()
{
	// Initialze all textures we use
	LoadTexture();

	return true;
}

void BOTextureManager::Shutdown()
{
	FreeAll();
	std::vector<SDL_Texture*>().swap(GetInstance().textureList);
}

void BOTextureManager::LoadTexture()
{
	SDL_Texture* texture;
	// balls
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/placeholderBoll10x10.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/placeholderBoll2.png");
	GetInstance().textureList.push_back(texture);
	// Hexagons
	texture = BOGraphicInterface::LoadTexture("Sprites/Blocks/BlockRegular.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Blocks/BlockArmored.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Blocks/BlockIndestructible.png");
	GetInstance().textureList.push_back(texture);
	// Hexagon with powerups
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagonPU1.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagonPU2.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagonPU3.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagonPU.png");
	GetInstance().textureList.push_back(texture);
	// Powerups
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderSheild.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderPowerupMultBall.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderPowerup2.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderPowerup3.png");
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
	// HUD
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/placeholderLife.png");
	GetInstance().textureList.push_back(texture);
	// Menu
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
	// The rest
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

}

void BOTextureManager::FreeTexture(int p_textureIndex)
{
	BOGraphicInterface::DestroyTexture(GetInstance().textureList[p_textureIndex]);
}

void BOTextureManager::FreeAll()
{
	for (int i = 0; i < GetInstance().textureList.size(); i++)
	{
		BOGraphicInterface::DestroyTexture(GetInstance().textureList[i]);
	}
	
}

SDL_Texture* BOTextureManager::GetTexture(Textures p_textureEnum)
{
	return GetInstance().textureList[p_textureEnum];
}
