#pragma once

#include <SFML/System.hpp>
#include <math.h>

float VecLength(sf::Vector2f a)
{
	return sqrtf(a.x * a.x + a.y * a.y);
}

void VecMul(sf::Vector2f &a, float f)
{
	a.x *= f;
	a.y *= f;
}

void VecNormalize(sf::Vector2f &a)
{
	float	w;

	w = sqrtf(a.x * a.x + a.y * a.y);
	a.x /= w;
	a.y /= w;
}

void VecSetLen(sf::Vector2f &a, float len)
{
	VecNormalize(a);
	VecMul(a, len);
}

float RandFloat(float max)
{
	float res = (float)rand() / (float)RAND_MAX;
	res *= max;
	return res;
}
