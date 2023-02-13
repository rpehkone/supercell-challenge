#pragma once

#include <memory>

#include "Controller.h"

namespace sf
{
	class Clock;
}

class ControllerAI : public Controller
{
public:
	ControllerAI(Game *pGame, Paddle *pPaddle);
	~ControllerAI();

	virtual bool initialise() override;
	virtual void update(float deltaTime) override;

private:
	std::unique_ptr<sf::Clock> m_pClock;
	float m_targetLocationY;
	float m_currentReactionTime;
};
