#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
#include "Pitch.h"

Pitch::Pitch(Game *pGame)
	: m_pGame(pGame)
{
}

Pitch::~Pitch()
{
}

bool Pitch::initialise(sf::Vector2f pitchSize)
{
	m_pitchSize = pitchSize;
	return true;
}

void Pitch::update(float deltaTime)
{
}

void Pitch::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	const float LineWidth = 6.f;
	sf::Vector2f size = target.getView().getSize();
	const float LineHeight = size.y;

	sf::Vector2f cursor((size.x - LineWidth) * 0.5f, 0.f);
	sf::RectangleShape rectangle(sf::Vector2f(LineWidth, LineHeight));
	rectangle.setFillColor(sf::Color(0xff, 0xff, 0xff, 0x40));
	rectangle.setPosition(cursor.x, cursor.y);
	target.draw(rectangle);
}
