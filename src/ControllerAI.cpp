#include <SFML/System.hpp>
#include <algorithm>
#include <iostream>
#include <math.h>

#include "ControllerAI.h"
#include "MathUtils.h"
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
	Game *game = getGame();

	//how many points player is leading
	int playerLeadsBy = (game->m_score[0] + 0) - game->m_score[1];
	//make ai react faster when player is in lead
	m_currentReactionTime = InitialAiReactionTime - playerLeadsBy * AiReactionTimeStepSize;
	m_currentReactionTime = max(m_currentReactionTime, 0);
#ifdef _DEBUG
	std::cout << playerLeadsBy << " " << m_currentReactionTime << " Init ai\n";
#endif
	m_targetLocationY = 0.f;
	return true;
}

void ControllerAI::update(float deltaTime)
{
	Game *game = getGame();

	if (m_pClock->getElapsedTime().asSeconds() >= m_currentReactionTime)
	{
		int ballidx = 0;
		if (game->m_numBalls == 2)
		{
			//find which ball is closer to ai
			const sf::Vector2f &bpos1 = game->getBall(0)->getPos();
			const sf::Vector2f &bpos2 = game->getBall(1)->getPos();
			if (bpos1.x < bpos2.x)
				ballidx = 1;
		}

		const sf::Vector2f &pitchSize = game->getPitch()->getPitchSize();
		const sf::Vector2f &bvel = game->getBall(ballidx)->getVel();
		const sf::Vector2f &bpos = game->getBall(ballidx)->getPos();

		float timeToHit = (game->getPitch()->getPitchSize().x - bpos.x) / bvel.x;
		m_targetLocationY = bpos.y + bvel.y * timeToHit;
		m_pClock->restart();
	}

	const float paddlePositionY = m_pPaddle->getPosition().y;
	const float offsetFromTarget = m_targetLocationY - paddlePositionY;
	if (fabs(offsetFromTarget) > 1.f)
	{
		const float maxMovement = AiPaddleMoveSpeed * deltaTime;
		const float movement = std::min(fabs(offsetFromTarget), maxMovement);
		m_pPaddle->move(offsetFromTarget < 0.f ? -movement : movement);
	}
}
