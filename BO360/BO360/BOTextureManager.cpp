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

void BOTextureManager::LoadTexture()
{
	SDL_Texture* texture;
	// balls
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/placeholderBoll10x10.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/placeholderBoll2.png");
	textureList.push_back(texture);
	// Hexagons
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagon40x40.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagon40x40red1.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagon40x40red2.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagon40x40red3.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Hexagons/placeholderHexagon40x40gray.png");
	textureList.push_back(texture);
	// Powerups
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderSheild.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderPowerupMultBall.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderPowerup2.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Powerups/placeholderPowerup3.png");
	textureList.push_back(texture);
	// Particles
	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/BallTrail.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/BallDebris.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/BlockDebris.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/PowerUpDebris.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/Explosion.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/DebugTrail.png");
	textureList.push_back(texture);
	// HUD
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/placeholderLife.png");
	textureList.push_back(texture);
	// Menu
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Menu/MenuEdge.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Menu/MenuBar.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Menu/MainMenuBackground.png");
	textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Menu/Button.png");
	textureList.push_back(texture);
}

void BOTextureManager::FreeTexture(int i)
{

}

void BOTextureManager::FreeAll()
{
	for (int i = 0; i < textureList.size(); i++)
	{
		textureList[i]->s;
	}
	
}
