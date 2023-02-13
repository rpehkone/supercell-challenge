#include <SFML/System.hpp>
#include <algorithm>
#include <math.h>

#include "ControllerAI.h"
#include "Paddle.h"
#include "Pitch.h"
#include "Game.h"
#include "Ball.h"

ControllerAI::ControllerAI(Game *pGame, Paddle *pPaddle)
	: Controller(pGame, pPaddle)
{
}

ControllerAI::~ControllerAI()
{
}

bool ControllerAI::initialise()
{
	m_pClock = std::make_unique<sf::Clock>();
	m_targetLocationY = 0.f;
	return true;
}

void ControllerAI::update(float deltaTime)
{
	if (m_pClock->getElapsedTime().asSeconds() >= 1.f)
	{
		Game *game = getGame();
		const sf::Vector2f &pitchSize = game->getPitch()->getPitchSize();
		// m_targetLocationY = (rand() % 100)*0.01f * (pitchSize.y-m_pPaddle->getPaddleHeight());
		const sf::Vector2f &bvel = game->getBall()->getVel();
		const sf::Vector2f &bpos = game->getBall()->getPos();
		m_targetLocationY = bpos.y;
		m_pClock->restart();
	}

	const float paddlePositionY = m_pPaddle->getPosition().y;
	const float offsetFromTarget = m_targetLocationY - paddlePositionY;
	if (fabs(offsetFromTarget) > 1.f)
	{
		const float maxMovement = PaddleMoveSpeed * deltaTime;
		const float movement = std::min(fabs(offsetFromTarget), maxMovement);
		m_pPaddle->move(offsetFromTarget < 0.f ? -movement : movement);
	}
}
