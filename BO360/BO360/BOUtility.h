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
	leftMouseKey
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
#endif