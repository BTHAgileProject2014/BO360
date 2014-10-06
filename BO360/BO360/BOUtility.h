#ifndef BOUTILITY_H_
#define BOUTILITY_H_
#include <math.h>
#include <iostream>

#define BALLDEBUGTRAIL 0

static const double PI = 3.14159265359;
static const double HALF_PI = PI * 0.5;
static const double DEGREES_TO_RADIANS = PI / 180;

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
	bool escKey;
};

enum GameState
{
	MENU,
	RUNNING,
	PAUSED,
	VICTORY,
	DEFEAT,
    HIGHSCORESTATE
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
	RETRY
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
	DUBBLEHP,
	KEY,
	INDESTRUCTIBLE
};

struct Block
{
	float2 m_position;
	BlockType m_type;
	int m_worth;
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
	zKey,
	xKey,
    fKey,
	escKey
};

enum Sound
{
	SOUND_POP,
	SOUND_DIE,
	SOUND_POWERUP,
	SOUND_TELEPORT,
	SOUND_BOUNCEONPAD
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

	box(float2 p_pos, int2 p_size)
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
	PUNone,
	PUBiggerPad,
	PUSmallerPad,
	PUShield,
	PUExtraBall,
    PUShockwave
};

inline void ThrowInitError(std::string p_className)
{
	std::cout << "Failed to initialize: " << p_className.c_str() << std::endl;
}

enum Textures
{
	TEXBALL,
	TEXDEBUGBALL,
	TEXHEXSTANDARD,
	TEXHEXARMORED,
	TEXHEXINDES,
	TEXHEXPU1,
	TEXHEXPU2,
	TEXHEXPU3,
    TEXHEXPUSHOCKWAVE,
	TEXHEXPU0,
	TEXSHIELD,
	TEXPUMULTIBALL,
	TEXPU2,
	TEXPU3,
    TEXPUSHOCKWAVE,
	TEXBALLTRAIL,
	TEXBALLDEBRIS,
	TEXBLOCKDEBRIS,
	TEXPUDEBRIS,
	TEXEXPLOSION,
	TEXDEBUGTRAIL,
	TEXLIFE,
	TEXMENUEDGE,
	TEXMENUBAR,
	TEXMENUBG,
	TEXMENUBUTTON,
	TEXMENUBUTTONHL,
	TEXBACKGROUND,
	TEXBLACKHOLE,
	TEXPADSEG,
	TEXTOOLTIP,
    TEXKEY
};

#endif