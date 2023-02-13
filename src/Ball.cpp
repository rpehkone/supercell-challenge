#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "MathUtils.h"
#include "Constants.h"
#include "Paddle.h"
#include "Pitch.h"
#include "Game.h"
#include "Ball.h"

Ball::Ball(Game *pGame)
	: m_pGame(pGame)
{
}

Ball::~Ball()
{
}

bool Ball::initialise()
{
	return true;
}

void Ball::update(float deltaTime)
{
	if (m_pGame->getState() == Game::State::WAITING)
	{
		// don't update the ball when we wait.
		return;
	}

	// check ball against boundaries of the pitch
	sf::Vector2f lastPosition = getPosition();
	sf::Vector2f newPosition = lastPosition + m_velocity * deltaTime;

	const sf::Vector2f pitchSize = m_pGame->getPitch()->getPitchSize();

	float ballTopPosition = newPosition.y - BallRadius;
	if (ballTopPosition < 0.f)
	{
		newPosition.y += ballTopPosition * 2.f;
		m_velocity.y = -m_velocity.y;
	}

	float ballBottomPosition = newPosition.y + BallRadius;
	if (ballBottomPosition > pitchSize.y)
	{
		newPosition.y -= (ballBottomPosition - pitchSize.y) * 2.f;
		m_velocity.y = -m_velocity.y;
	}

	newPosition.y = std::clamp(newPosition.y, 0.01f + BallRadius, pitchSize.y - 0.01f - BallRadius);

	// check ball against paddles
	const Side sideToTest = (newPosition.x < pitchSize.x * 0.5f) ? Side::LEFT : Side::RIGHT;
	const Paddle *pPaddleToTest = m_pGame->getPaddle(sideToTest);
	const sf::FloatRect paddleRect = pPaddleToTest->getRect();

	const sf::Vector2f closestPointOnPaddle(
		std::clamp(newPosition.x, paddleRect.left, paddleRect.left + paddleRect.width),
		std::clamp(newPosition.y, paddleRect.top, paddleRect.top + paddleRect.height));
	const sf::Vector2f paddleToBall = newPosition - closestPointOnPaddle;
	const bool intersects = VecLength(paddleToBall) < BallRadius;
	if (intersects)
	{
		m_velocity.x = sideToTest == Side::LEFT ? fabs(m_velocity.x) : -fabs(m_velocity.x);
		in_collision = true;
	}
	else if (in_collision)
	{
		in_collision = false;
		//increase velocity on paddle bounce
		VecMul(m_velocity, 1.05f);
		//add random variation to bounce direction
		m_velocity.y += RandFloat(50.0);
	}

	// set the position and check for a goal
	setPosition(newPosition);

	if (newPosition.x + BallRadius < 0.f)
	{
		m_pGame->scoreGoal(Side::RIGHT);
	}
	else if (newPosition.x - BallRadius > pitchSize.x)
	{
		m_pGame->scoreGoal(Side::LEFT);
	}
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (m_pGame->getState() == Game::State::WAITING)
	{
		// don't render the ball when we wait.
		return;
	}

	sf::CircleShape circle(BallRadius, BallPoints);
	circle.setFillColor(sf::Color::White);
	circle.setPosition(getPosition() - sf::Vector2f(BallRadius, BallRadius));
	target.draw(circle);
}

void Ball::fireFromCenter()
{
	sf::Vector2f pitchSize = m_pGame->getPitch()->getPitchSize();
	setPosition(pitchSize * 0.5f);

	m_velocity.x = 500.0f;
	if (rand() % 2)
		m_velocity.x *= -1.0;
	m_velocity.y = RandFloat(1000.0f);
	VecSetLen(m_velocity, FiringSpeed);
}
