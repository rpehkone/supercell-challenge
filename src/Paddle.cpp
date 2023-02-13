#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Paddle.h"
#include "Pitch.h"
#include "Game.h"

Paddle::Paddle(Game *pGame)
	: m_pGame(pGame)
{
}

Paddle::~Paddle()
{
}

bool Paddle::initialise(Side side, uint32_t color)
{
	m_side = side;
	m_color = color;

	const sf::Vector2f &pitchSize = m_pGame->getPitch()->getPitchSize();
	const float XPosition = (m_side == Side::LEFT) ? PaddleOffsetFromEdge : pitchSize.x - PaddleOffsetFromEdge - PaddleWidth;
	setPosition(sf::Vector2f(XPosition, pitchSize.y * 0.5f));

	return true;
}

void Paddle::update(float deltaTime)
{
}

void Paddle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::RectangleShape paddleRect(sf::Vector2f(PaddleWidth, PaddleHeight));
	paddleRect.setFillColor(sf::Color(m_color));
	paddleRect.setPosition(getPosition());
	target.draw(paddleRect);
}

sf::FloatRect Paddle::getRect() const
{
	return sf::FloatRect(getPosition(), sf::Vector2f(PaddleWidth, PaddleHeight));
}

float Paddle::getPaddleHeight() const
{
	return PaddleHeight;
}

uint32_t Paddle::getPaddleColor() const
{
	return m_color;
}

void Paddle::move(float yDelta)
{
	sf::Vector2f position = getPosition();
	position.y += yDelta;

	const sf::Vector2f &pitchSize = m_pGame->getPitch()->getPitchSize();
	position.y = std::clamp(position.y, 0.f, pitchSize.y - PaddleHeight);

	setPosition(position);
}
