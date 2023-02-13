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
