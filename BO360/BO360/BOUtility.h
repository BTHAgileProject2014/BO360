#ifndef BOUTILITY_H_
#define BOUTILITY_H_
#include <math.h>

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

	float length()
	{
		return (float)sqrt(x*x + y*y);
	}

	float2 normalized()
	{
		float2 normalizedFloat;
		float lengthFloat;
		lengthFloat = length();
		normalizedFloat.x = x / lengthFloat;
		normalizedFloat.y = y / lengthFloat;
		return normalizedFloat;
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
	spacebarKey
};

// Sphere for collision check
struct sphere
{
	float2 pos;
	int radius;

	sphere()
	{

	}

	sphere(float2 p_pos, int p_radius)
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

		top = (int)p_pos.y;
		bottom = (int)p_pos.y + size.y;
		left = (int)p_pos.x;
		right = (int)p_pos.x + size.x;
	}
};

struct hexagon
{
	float2 pos;
	int2 size;
	float2 pointUpLeft, pointUpRight, pointRight, pointDownRight, pointDownLeft, pointLeft;
	float2 offset;

	hexagon(){}

	hexagon(float2 p_pos, int2 p_size)
	{
		offset = float2(40, 40);
		
		pointUpLeft.x = p_pos.x - 19;
		pointUpLeft.y = p_pos.y - 34;

		pointUpRight.x = p_pos.x + 20;
		pointUpRight.y = p_pos.y - 34;

		pointRight.x = p_pos.x + 40;
		pointRight.y = p_pos.y;

		pointDownRight.x = p_pos.x + 20;
		pointDownRight.y = p_pos.y - 35;

		pointDownLeft.x = p_pos.x - 19;
		pointDownLeft.y = p_pos.y - 35;

		pointLeft.x = p_pos.x - 39;
		pointLeft.y = p_pos.y;
	}
};
#endif