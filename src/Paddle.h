#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "Constants.h"

class Game;

class Paddle : public sf::Drawable, public sf::Transformable
{
public:
	Paddle(Game *pGame);
	~Paddle();

	bool initialise(Side side, uint32_t color);
	void update(float deltaTime);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	sf::FloatRect getRect() const;
	float getPaddleHeight() const;
	uint32_t getPaddleColor() const;
	void move(float yDelta);

private:
	uint32_t m_color;
	Game *m_pGame;
	Side m_side;
};
