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
#endif