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

    // Power up blocks, loaded using theme.
    filename = theme + "/Blocks/BlockPowerUp.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Power up block texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

    filename = theme + "/Blocks/BlockRegularLargerPad.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Larger pad block texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

    filename = theme + "/Blocks/BlockRegularShield.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Shield block texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

    filename = theme + "/Blocks/BlockRegularAddBall.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Add ball block texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

    filename = theme + "/Blocks/BlockRegularFireball.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Fireball block texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

    filename = theme + "/Blocks/BlockRegularShockwave.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Shockwave block texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

    filename = theme + "/Blocks/BlockRegularStickyPad.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Sticky pad block texture failed to load!" << std::endl;
        std::cin.get();
    }
    GetInstance().textureList.push_back(texture);

    filename = theme + "/Blocks/BlockRegularSlowTime.png";
    texture = BOGraphicInterface::LoadTexture(filename);
    if (!texture)
    {
        std::cout << "Slowtime block texture failed to load!" << std::endl;
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

	// Power ups.
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
	texture = BOGraphicInterface::LoadTexture("Sprites/Map/DebugDirection.png");
	GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Tooltip.png");
    GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/HexagonAvailable.png");
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/HexagonChosen.png");
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/HexagonHighlighted.png");
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/HexagonLocked.png");
    GetInstance().textureList.push_back(texture);

    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTSHOCKWAVE
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTMULTISPAWN
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTDECREASECD
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTQUANTUMFUEL
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTPOWERUPBOOST1
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 2/SlowTimeDuration.png");//TEXTTSLOWTIME
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 2/BallDamage.png");//TEXTTINCREASEBALLDAMAGE  
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 2/FireballDuration.png");//TEXTTFIREBALL
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTPOWERUPBOOST2
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 1/PowerUpSpeedMinus.png");//TEXTTDECREASEPOWERUPFALLSPEED2
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 1/PowerUpGift.png");//TEXTTPOWERUPGIFT
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 1/LessGravity.png");//TEXTTDECREASEGRAVITYPULL
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTMULTIBALL
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTMEGAPAD
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 2/StartShield.png");//TEXTTSTARTWITHSHIELD
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Start.png");//TEXTTDROPBASICPOWERUP
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 1/SlowerBall.png");//TEXTTDECREASEBALLSPEED 
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 2/FuelRefill.png");//TEXTTMOREFUELATREFILL
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTSUPERTANK
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTSTACKABLESHIELD
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 2/StickyPadDuration.png");//TEXTTSTICKYPAD
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 1/ExtraShield.png");//TEXTTADDBOUNCETOSHIELD
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 1/QuickerPad.png");//TEXTTINCREASEPADSPEED
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 2/BallCollisionFuel.png");//TEXTTBALLSGETFUELWHENTHEYCOLLIDE
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTDOUBLEMULTIBALL
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTINCREASESTARTPADSIZE
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 2/MaxPadSize.png");//TEXTTINCREASEMAXPADSIZE
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Tier 2/DoubleSizeIncrease.png");//TEXTTCHANCETODOUBLEPADSIZEINCREASE
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTREGENERATE
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTINCREASESTARTPAD
    GetInstance().textureList.push_back(texture);
    texture = BOGraphicInterface::LoadTexture("Sprites/Tech Tree/Icons/Empty.png");//TEXTTGIANTBALL
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
