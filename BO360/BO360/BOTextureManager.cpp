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
	texture = BOGraphicInterface::LoadTexture("Sprites/Map/Ball.png");
    if (!texture)
    {
        std::cout << "Ball texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/Map/Thruster.png");
    if (!texture)
    {
        std::cout << "Ball thruster texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Power Ups/Fireball.png");
    if (!texture)
    {
        std::cout << "Fireball texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	// Hexagons, loaded using the theme.
    const std::string theme = "Sprites/Themes/" + p_theme;
    std::string filename;

    filename = theme + "/Blocks/BlockRegular.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Regular block texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    filename = theme + "/Blocks/BlockPowerUp.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Power up block texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

    filename = theme + "/Blocks/BlockDouble.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Double block texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

    filename = theme + "/Blocks/BlockArmored.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Armored block texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    filename = theme + "/Blocks/BlockIndestructible.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Indestructible block texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    // Glows, loaded using the theme.
    filename = theme + "/Glows/GlowRegular.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Regular glow texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    filename = theme + "/Glows/GlowDouble.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Double glow texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

    filename = theme + "/Glows/GlowArmored.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Armored glow texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    filename = theme + "/Glows/GlowIndestructible.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Indestructible glow texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	// Powerups.
	texture = BOGraphicInterface::LoadTexture("Sprites/Power Ups/Shield.png");
    if (!texture)
    {
        std::cout << "Shield texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/Power Ups/Shockwave.png");
    if (!texture)
    {
        std::cout << "Shockwave texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/Power Ups/StickyPad.png");
    if (!texture)
    {
        std::cout << "Sticky Pad texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Power Ups/PowerUpAddBall.png");
    if (!texture)
    {
        std::cout << "Add ball power up texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Power Ups/PowerUpFireball.png");
    if (!texture)
    {
        std::cout << "Fireball power up texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Power Ups/PowerUpShield.png");
    if (!texture)
    {
        std::cout << "Shield power up texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture); 

	texture = BOGraphicInterface::LoadTexture("Sprites/Power Ups/PowerUpBiggerPad.png");
    if (!texture)
    {
        std::cout << "Bigger pad power up texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/Power Ups/PowerUpStickyPad.png");
    if (!texture)
    {
        std::cout << "Sticky pad power up texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/Power Ups/PowerUpShockwave.png");
    if (!texture)
    {
        std::cout << "Shockwave power up texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/Power Ups/PowerUpSlowTime.png");
    if (!texture)
    {
        std::cout << "Slow time power up texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	// Particles
	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/BallTrail.png");
    if (!texture)
    {
        std::cout << "Ball trail particle texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/Particles/FireballTrail.png");
    if (!texture)
    {
        std::cout << "Fireball trail particle texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/BallDebris.png");
    if (!texture)
    {
        std::cout << "Ball debris particle texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/BlockDebris.png");
    if (!texture)
    {
        std::cout << "Block debris particle texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/PowerUpDebris.png");
    if (!texture)
    {
        std::cout << "Power up debris particle texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/Explosion.png");
    if (!texture)
    {
        std::cout << "Explosion particle texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Particles/DebugTrail.png");
    if (!texture)
    {
        std::cout << "Debug trail particle texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	// HUD.
	texture = BOGraphicInterface::LoadTexture("Sprites/HUD/Alive.png");
    if (!texture)
    {
        std::cout << "Fireball trail particle texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/HUD/Dead.png");
    if (!texture)
    {
        std::cout << "Fireball trail particle texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/HUD/Core.png");
    if (!texture)
    {
        std::cout << "Fireball trail particle texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	// Menu.
	texture = BOGraphicInterface::LoadTexture("Sprites/Menu/MenuEdge.png");
    if (!texture)
    {
        std::cout << "Menu edge texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Menu/MenuBar.png");
    if (!texture)
    {
        std::cout << "Menu bar texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Menu/MainMenuBackground.png");
    if (!texture)
    {
        std::cout << "Menu background texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/Menu/GrayBackground.png");
    if (!texture)
    {
        std::cout << "Gray Menu background texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Menu/Button.png");
    if (!texture)
    {
        std::cout << "Menu button texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Menu/ButtonHighlighted.png");
    if (!texture)
    {
        std::cout << "Menu highlighted button texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/Menu/ButtonToolTip.png");
    if (!texture)
    {
        std::cout << "Menu button tooltip texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	// Map textures.
	texture = BOGraphicInterface::LoadTexture("Sprites/Map/Background.png");
    if (!texture)
    {
        std::cout << "Background texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Map/BlackHole.png");
    if (!texture)
    {
        std::cout << "Black hole texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/Map/PadSegment.png");
    if (!texture)
    {
        std::cout << "Pad segment texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/Map/Core.png");
    if (!texture)
    {
        std::cout << "Map core texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

	texture = BOGraphicInterface::LoadTexture("Sprites/HUD/Lock.png");
    if (!texture)
    {
        std::cout << "Level selector lock texture failed to load!" << std::endl;
        std::cin.get();
    }
	GetInstance().textureList.push_back(texture);

    // Tech Tree
	texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/DEBUGDIR.png");
	GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Tooltip.png");
    GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/canChooseTech.png");
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/highlightTech.png");
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/disabledTech.png");
    GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTSHOCKWAVE
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTMULTISPAWN
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTDECREASECD
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTQUANTUMFUEL
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTPOWERUPBOOST1
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTSLOWTIME
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//7 TEXTTINCREASEBALLDAMAGE
    GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTFIREBALL
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTPOWERUPBOOST2
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTDECREASEPOWERUPFALLSPEED2
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTPOWERUPGIFT
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTDECREASEGRAVITYPULL
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTMULTIBALL
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//7 TEXTTMEGAPAD
    GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTSTARTWITHSHIELD
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTDECREASEPOWERUPFALLSPEED
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTDROPBASICPOWERUP
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTDECREASEBALLSPEED
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTMOREFUELATREFILL
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTSUPERTANK
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//7TEXTTSTACKABLESHIELD
    GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTSTICKYPAD
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTADDBOUNCETOSHIELD
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTINCREASEPADSPEED
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTBALLSGETFUELWHENTHEYCOLLIDE
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTDOUBLEMULTIBALL
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTINCREASESTARTPADSIZE
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//7 TEXTTINCREASEMAXPADSIZE
    GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTCHANCETODOUBLEPADSIZEINCREASE
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTREGENERATE
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/PlaceHolderPNG/Techs/activeTech.png");//TEXTTINCREASESTARTPAD
    GetInstance().textureList.push_back(texture);

	GetInstance().textureList.push_back(NULL);// Lägg in en tom för att fixa nrOfLevels
	texture = BOGraphicInterface::LoadTexture("Maps/button1Map.png");
	GetInstance().textureList.push_back(texture);
	texture = BOGraphicInterface::LoadTexture("Maps/button2Map.png");
	GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Maps/button3Map.png");
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Maps/button4Map.png");
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Maps/button5Map.png");
	GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Maps/button6Map.png");
	GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Maps/button7Map.png");
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
