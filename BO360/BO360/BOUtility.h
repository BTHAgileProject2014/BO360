#ifndef BOUTILITY_H_
#define BOUTILITY_H_
#include <math.h>
#include <iostream>

#define BALLDEBUGTRAIL 0

static const double PI = 3.14159265359;
static const double HALF_PI = PI * 0.5;
static const double DEGREES_TO_RADIANS = PI / 180;
static const double RADIANS_TO_DEGREES = 180 / PI;

// Floating point value structs.
struct float2
{
	float x, y;

	float2()
	{

	}

	float2(float p_x, float p_y)
	{
		x = p_x;
		y = p_y;
	}

	float length()const
	{
		return (float)sqrt(x*x + y*y);
	}

	float2 normalized()const
	{
		float2 normalizedFloat;
		float lengthFloat;
		lengthFloat = length();
		normalizedFloat.x = x / lengthFloat;
		normalizedFloat.y = y / lengthFloat;
		return normalizedFloat;
	}

	void normalize()
	{
		float2 normalizedFloat;
		float lengthFloat;
		lengthFloat = length();
		normalizedFloat.x = x / lengthFloat;
		normalizedFloat.y = y / lengthFloat;
		x = normalizedFloat.x;
		y = normalizedFloat.y;
	}

	float2 operator+(const float2 p_input)
	{
		float2 temp;
		temp.x = (x + p_input.x);
		temp.y = (y + p_input.y);

		return temp;
	}

    float2 operator-()
    {
        float2 temp;
        temp.x = -x;
        temp.y = -y;

        return temp;
    }

	float2 operator-(const float2 p_input)
	{
		float2 temp;
		temp.x = (x - p_input.x);
		temp.y = (y - p_input.y);

		return temp;
	}

	float2 operator*(const float p_input)
	{
		float2 temp;
		temp.x = x * p_input;
		temp.y = y * p_input;

		return temp;
	}

	float2 scalar(float p_input)
	{
		return float2(x * p_input, y * p_input);
	}

	float dot(float2 p_input)
	{
		return ((x * p_input.x) + (y * p_input.y));
	}
};

struct float3
{
	float x, y, z;

	float3()
	{

	}

	float3(float p_x, float p_y, float p_z)
	{
		x = p_x;
		y = p_y;
		z = p_z;
	}

	float length()
	{
		return (float)sqrt(x*x + y*y + z*z);
	}

	float3 normalized()
	{
		float3 normalizedFloat;
		float lengthFloat;
		lengthFloat = length();
		normalizedFloat.x = x / lengthFloat;
		normalizedFloat.y = y / lengthFloat;
		normalizedFloat.z = z / lengthFloat;
		return normalizedFloat;
	}

	void normalize()
	{
		float3 normalizedFloat;
		float lengthFloat;
		lengthFloat = length();
		normalizedFloat.x = x / lengthFloat;
		normalizedFloat.y = y / lengthFloat;
		normalizedFloat.z = z / lengthFloat;
		x = normalizedFloat.x;
		y = normalizedFloat.y;
		z = normalizedFloat.z;
	}


	float3 operator+(const float3 p_input)
	{
		float3 temp;
		temp.x = (x + p_input.x);
		temp.y = (y + p_input.y);
		temp.z = (z + p_input.z);

		return temp;
	}

	float3 operator-(const float3 p_input)
	{
		float3 temp;
		temp.x = (x - p_input.x);
		temp.y = (y - p_input.y);
		temp.z = (z - p_input.z);

		return temp;
	}
};

struct float4
{
	float x, y, z, w;

	float4()
	{

	}

	float4(float p_x, float p_y, float p_z, float p_w)
	{
		x = p_x;
		y = p_y;
		z = p_z;
		w = p_w;
	}

	float length()
	{
		return (float)sqrt(x*x + y*y + z*z + w*w);
	}

	float4 normalized()
	{
		float4 normalizedFloat;
		float lengthFloat;
		lengthFloat = length();
		normalizedFloat.x = x / lengthFloat;
		normalizedFloat.y = y / lengthFloat;
		normalizedFloat.z = z / lengthFloat;
		normalizedFloat.w = w / lengthFloat;
		return normalizedFloat;
	}

	float4 operator+(const float4 p_input)
	{
		float4 temp;
		temp.x = (x + p_input.x);
		temp.y = (y + p_input.y);
		temp.z = (z + p_input.z);
		temp.w = (w + p_input.w);

		return temp;
	}

	float4 operator-(const float4 p_input)
	{
		float4 temp;
		temp.x = (x - p_input.x);
		temp.y = (y - p_input.y);
		temp.z = (z - p_input.z);
		temp.w = (w - p_input.w);

		return temp;
	}
};

// Integer value structs.
struct int2
{
	int x, y;

	int2()
	{

	}

	int2(int p_x, int p_y)
	{
		x = p_x;
		y = p_y;
	}

	float length()
	{
		return (float)sqrt((float)(x*x) + (float)(y*y));
	}

	int2 operator+(const int2 p_input)
	{
		int2 temp;
		temp.x = (x + p_input.x);
		temp.y = (y + p_input.y);

		return temp;
	}

	int2 operator-(const int2 p_input)
	{
		int2 temp;
		temp.x = (x - p_input.x);
		temp.y = (y - p_input.y);

		return temp;
	}
};

struct int3
{
	int x, y, z;

	int3()
	{

	}

	int3(int p_x, int p_y, int p_z)
	{
		x = p_x;
		y = p_y;
		z = p_z;
	}

	float length()
	{
		return (float)sqrt((float)(x*x) + (float)(y*y) + (float)(z*z));
	}

	int3 operator+(const int3 p_input)
	{
		int3 temp;
		temp.x = (x + p_input.x);
		temp.y = (y + p_input.y);
		temp.z = (z + p_input.z);

		return temp;
	}

	int3 operator-(const int3 p_input)
	{
		int3 temp;
		temp.x = (x - p_input.x);
		temp.y = (y - p_input.y);
		temp.z = (z - p_input.z);

		return temp;
	}
};

struct int4
{
	int x, y, z, w;

	int4()
	{

	}

	int4(int p_x, int p_y, int p_z, int p_w)
	{
		x = p_x;
		y = p_y;
		z = p_z;
		w = p_w;
	}

	float length()
	{
		return (float)sqrt((float)(x*x) + (float)(y*y) + (float)(z*z) + (float)(w*w));
	}

	int4 operator+(const int4 p_input)
	{
		int4 temp;
		temp.x = (x + p_input.x);
		temp.y = (y + p_input.y);
		temp.z = (z + p_input.z);
		temp.w = (w + p_input.w);

		return temp;
	}

	int4 operator-(const int4 p_input)
	{
		int4 temp;
		temp.x = (x - p_input.x);
		temp.y = (y - p_input.y);
		temp.z = (z - p_input.z);
		temp.w = (w - p_input.w);

		return temp;
	}
};

// Key messages for input
struct InputMessages
{
	int mouseX;
	int mouseY;
	bool leftMouseKey;
	bool rightMouseKey;
	bool middleMouseKey;
	bool spacebarKey;
	bool rightArrow;
	bool leftArrow;
	bool upArrow;
	bool downArrow;
	bool zKey;
	bool xKey;
    bool fKey;
    bool tKey;
	bool gKey;
	bool hKey;
	bool jKey;
	bool mKey;
	bool escKey;
    bool enterKey;
};

enum GameState
{
	MENU,
	RUNNING,
	PAUSED,
	VICTORY,
	DEFEAT,
    HIGHSCORESTATE,
	LEVELSELECTOR,
    TECHTREE,
    CUTSCENE
};

enum ButtonAction
{
	NOACTION,

	QUIT,
	EXIT,
	STORY,
    HIGHSCORE,

	RESUME,
	NEXT,
	RETRY,

	LEVELSELECT,
	LEVEL,

    TECHTREEACTION,
    TECHTREERESET,

    CUTSCENENEXT,
    CUTSCENEPREVIOUS,
    CUTSCENEPLAY
};

enum ParticleType
{
	BALLTRAIL,
	BALLDEBRIS,
	BLOCKDEBRIS,
	EXPLOSION,
	POWERUPDEBRIS,
	DEBUGTRAIL,

	m_numberOfParticleTypes
};

enum BlockType
{
	REGULAR,
    DOUBLE,
    ARMORED,
	KEY,
	INDESTRUCTIBLE
};

enum KeyMessages
{
	upArrow,
	downArrow,
	rightArrow,
	leftArrow,
	leftMouseKey,
	rightMouseKey,
	middleMouseKey,
	spacebarKey,
    enterKey,
	zKey,
	xKey,
    fKey,
    tKey,
	gKey,
	hKey,
	jKey,
	mKey,
	escKey
};

enum Sound
{
    SOUND_MUSIC,
    SOUND_MENUMUSIC,
    SOUND_BOSSMUSIC,
	SOUND_POP,
	SOUND_DIE,
	SOUND_POWERUP,
	SOUND_TELEPORT,
	SOUND_BOUNCEONPAD,
    SOUND_CHARGE,
    SOUND_SHOCKWAVE,
    SOUND_SLOWDOWN,
    SOUND_SLOWUP,
    SOUND_THRUSTER,
    SOUND_FUEL,
    SOUND_BUMP
};

// Sphere for collision check
struct sphere
{
	float2 pos;
	float radius;

	sphere()
	{

	}

	sphere(float2 p_pos, float p_radius)
	{
		pos = p_pos;
		radius = p_radius;
	}
};

struct box
{
	float2 pos;
	int2 size;
	int top, bottom, left, right;

	box()
	{

	}

	box(const float2 p_pos, const int2 p_size)
	{
		pos = p_pos;
		size = p_size;

		top = (int)p_pos.y - (size.y / 2);
		bottom = (int)p_pos.y + (size.y/2);
		left = (int)p_pos.x - (size.x / 2);
		right = (int)p_pos.x + (size.x/2);
	}
};

struct hexagon
{
	float2 pos;
	int2 size;
	float2 pointUpLeft, pointUpRight, pointRight, pointDownRight, pointDownLeft, pointLeft;

	hexagon(){}

	hexagon(float2 p_pos, int2 p_size)
	{
		pos = p_pos;
		size = p_size;
		
		pointUpLeft.x = p_pos.x - 10; //(p_size.x / 4.0f);
		pointUpLeft.y = p_pos.y - 17; //(p_size.y / 2.28f);

		pointUpRight.x = p_pos.x + 9; // (p_size.x / 4.0f);
		pointUpRight.y = p_pos.y - 17; // (p_size.y / 2.28f);

		pointRight.x = p_pos.x + 19; // (p_size.x / 2.0f);
		pointRight.y = p_pos.y;

		pointDownRight.x = p_pos.x + 9; // (p_size.x / 4.0f);
		pointDownRight.y = p_pos.y + 16; // (p_size.y / 2.28f);

		pointDownLeft.x = p_pos.x - 10; // (p_size.x / 4.0f);
		pointDownLeft.y = p_pos.y + 16; // (p_size.y / 2.28f);

		pointLeft.x = p_pos.x - 20; // (p_size.x / 2.0f);
		pointLeft.y = p_pos.y;
	}
};

// What types of power-ups we use
enum PowerUpTypes
{
	PUNone = 0,
	PUBiggerPad,
	PUSmallerPad,
	PUShield,
	PUExtraBall,
	PUFireBall,
    PUShockwave,
    PUStickyPad,
    PUSlowTime,
    PURandom
};

struct Block
{
    float2 m_position;
    BlockType m_type;
    int m_worth;
    PowerUpTypes m_powerUpType;
};

inline void ThrowInitError(std::string p_className)
{
	std::cout << "Failed to initialize: " << p_className.c_str() << std::endl;
}

enum Textures
{
    // Balls.
	TEXBALL,
    TEXBALLTAIL,
	TEXFIREBALL,

    // Blocks.
	TEXHEXSTANDARD,
    TEXHEXDOUBLE,
    TEXHEXARMORED,
    TEXHEXINDES,
    TEXHEXBOSSCORE,

    // Blocks with power ups.
    TEXHEXPOWERUP,
    TEXHEXPUBIGGERPAD,
    TEXHEXPUSHIELD,
    TEXHEXPUADDBALL,
    TEXHEXPUFIREBALL,
    TEXHEXPUSHOCKWAVE,
    TEXHEXPUSTICKYPAD,
    TEXHEXPUSLOWTIME,

    // Glows.
    TEXGLOWSTANDARD,
    TEXGLOWDOUBLE,
    TEXGLOWARMORED,
    TEXGLOWINDES,

    // Power ups.
	TEXSHIELD,
    TEXSHOCKWAVE,
    TEXSTICKYPAD,
	TEXPUADDBALL,
	TEXPUFIREBALL,
	TEXPUSHIELD,
	TEXPUBIGGERPAD,
    TEXPUSTICKYPAD,
    TEXPUSHOCKWAVE,
    TEXPUSLOWTIME,

    // Particles.
	TEXBALLTRAIL,
    TEXFIREBALLTRAIL,
	TEXBALLDEBRIS,
	TEXBLOCKDEBRIS,
	TEXPUDEBRIS,
	TEXEXPLOSION,
	TEXDEBUGTRAIL,

    // HUD.
	TEXHUDALIVE,
    TEXHUDDEAD,
    TEXHUDCORE,
    TEXHUDBAR,
    TEXHUDMEGAPAD,
    TEXHUDQUANTUMFUEL,
    TEXHUDGIANTBALL,

    // Menu.
	TEXMENUEDGE,
	TEXMENUBAR,
	TEXMENUBG,
    TEXMENUGRAY,
	TEXMENUBUTTON,
	TEXMENUBUTTONHL,
    TEXTOOLTIP,

    // Map.
	TEXBACKGROUND,
	TEXBLACKHOLE,
	TEXPADSEG,
    TEXKEY,
	TEXLOCK,

    // Tech tree.
	TEXTTBG,
	TEXDEBUGDIR,
    TEXTTTOLTIPFRAME,

    TEXTTADJACENTACTIVE,
    TEXTTCHOSEN,
    TEXTTHIGHLIGHTED,
    TEXTTINACTIVE,

    TEXTTSHOCKWAVE,
    TEXTTMULTISPAWN,
    TEXTTDECREASECD,
    TEXTTQUANTUMFUEL,
    TEXTTPOWERUPBOOST1,
    TEXTTSLOWTIME,
    TEXTTINCREASEBALLDAMAGE,
    TEXTTFIREBALL,
    TEXTTPOWERUPBOOST2,
    TEXTTDECREASEPOWERUPFALLSPEED,

    TEXTTPOWERUPGIFT,
    TEXTTDECREASEGRAVITYPULL,    
    TEXTTMULTIBALL,
    TEXTTMEGAPAD,
    TEXTTSTARTWITHSHIELD,
    TEXTTDROPBASICPOWERUP,
    TEXTTDECREASEBALLSPEED,
    TEXTTMOREFUELATREFILL,
    TEXTTSUPERTANK,
    TEXTTSTACKABLESHIELD,

    TEXTTSTICKYPAD,
    TEXTTADDBOUNCETOSHIELD,
    TEXTTINCREASEPADSPEED,
    TEXTTBALLSGETFUELWHENTHEYCOLLIDE,
    TEXTTDOUBLEMULTIBALL,
    TEXTTINCREASESTARTPADSIZE,
    TEXTTINCREASEMAXPADSIZE,
    TEXTTCHANCETODOUBLEPADSIZEINCREASE,
    TEXTTREGENERATE,
    TEXTTINCREASESTARTPAD,

    TEXTTGIANTBALL,

    // Cutscenes.
    TEXCUTSCENETEXTBACKGROUND,
    TEXCUTSCENETEXTFRAME,

	// Only maps from here on.
	nrOfLevels,
	TEXBUTTON1MAP,
	TEXBUTTON2MAP,
    TEXBUTTON3MAP,
    TEXBUTTON4MAP,
    TEXBUTTON5MAP,
    TEXBUTTON6MAP,
    TEXBUTTON7MAP,
    TEXBUTTON8MAP,
    TEXBUTTON9MAP,
    TEXBUTTON10MAP,
    TEXBUTTON11MAP,
    TEXBUTTON12MAP,
    TEXBUTTON13MAP,
    TEXBUTTON14MAP,
    TEXBUTTON15MAP,
    TEXBUTTON16MAP,
	
	texNR

};

enum TTEffects
{

    //List order
    //Lane 1
    ShockWave,
    MultiSpawn3,
    DecreaseCD,
    QuantumFuel,
    //Lane 2
    PowerUpBoost1,
    SlowTime,
    IncreaseBallDamage2,
    Fireball,
    MultiSpawn2,
    //Lane 3
    PowerUpBoost2,
    DecreasePowerUpFallSpeed2,
    PowerUpGift,
    DecreaseGravityPull,
    IncreaseBallDamage,
    DoubleMultiBall2,
    //Lane 4
    MegaPad,
    StartWithShield,
    DecreasePowerUpFallSpeed,
    DropBasicPowerUp,    
    DecreaseBallSpeed,
    MoreFuelAtRefill,
    SuperTank,
    //Lane 5
    StackableShield,
    StickyPad,
    AddBounceToShield,
    IncreasePadSpeed,
    BallsGetFuelWhenTheyCollide,
    DoubleMultiBall,
    //Lane 6
    IncreaseStartPadSize,
    IncreaseMaxPadSize,
    ChanceDoublePadSizeIncrease, 
    IncreaseMaxPadSize2,
    MuliSpawn, 
    //Lane 7
    Regenerate,
    IncreaseStartPadSize2,
    ChanceDoublePadSizeIncrease2,
    GiantBall

    /*//In order
    //Layer 1
    DecreasePowerUpFallSpeed,   //decrease 10%
    AddBounceToShield,          //Increase bounce on shield 
    IncreasePadSpeed,           //
    DecreaseBallSpeed,
    DecreaseGravityPull,
    PowerUpGift,
    //Layer 2
    DecreasePowerUpFallSpeed2,   //20% slower
    StartWithShield,             //Start with a shield
    StickyPad,
    IncreaseMaxPadSize,
    ChanceDoublePadSizeIncrease, // 33% chance to get double effekt
    IncreaseMaxPadSize2,
    BallsGetFuelWhenTheyCollide,
    MoreFuelAtRefill,
    IncreaseBallDamage,
    Fireball,
    IncreaseBallDamage2,
    SlowTime,
    //Layer 3
    PowerUpBoost1,
    PowerUpBoost2,
    MegaPad,
    StackableShield,
    IncreaseStartPadSize,
    Regenerate,
    IncreaseStartPadSize2,
    ChanceDoublePadSizeIncrease2,
    GiantBall,
    MuliSpawn,
    DoubleMultiBall,
    SuperTank,                  //Bounce on block doesn't remove fuel
    DoubleMultiBall2,
    MultiSpawn2,
    QuantumFuel,
    DoubleMultiBall3,
    PowerUpBoost3,
    ShockWave
    */
};

#endif