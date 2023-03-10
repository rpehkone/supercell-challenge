#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

class Game;

class Ball : public sf::Drawable, public sf::Transformable
{
public:
	Ball(Game *pGame);
	~Ball();

	bool initialise();
	void update(float deltaTime);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void fireFromCenter(bool go_left);
	const sf::Vector2f &getVel() const { return m_velocity; };
	const sf::Vector2f &getPos() const { return getPosition(); };

private:
	Game *m_pGame;
	sf::Vector2f m_velocity;
	bool in_collision;
};
