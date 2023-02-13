#pragma once

#include <SFML/System.hpp>
#include <math.h>

inline float min(float a,float b)
{
	return a < b ? a : b;
}

inline float max(float a,float b)
{
	return a > b ? a : b;
}

inline float VecLength(sf::Vector2f a)
{
	return sqrtf(a.x * a.x + a.y * a.y);
}

inline void VecMul(sf::Vector2f &a, float f)
{
	a.x *= f;
	a.y *= f;
}

inline void VecNormalize(sf::Vector2f &a)
{
	float	w;

	w = sqrtf(a.x * a.x + a.y * a.y);
	a.x /= w;
	a.y /= w;
}

inline void VecSetLen(sf::Vector2f &a, float len)
{
	VecNormalize(a);
	VecMul(a, len);
}

inline float RandFloat(float max)
{
	float res = (float)rand() / (float)RAND_MAX;
	res *= max;
	return res;
}

inline bool RandBool()
{
	return (bool)(rand() % 2);
}
