#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

#include "AudioVisual.h"
#include "Constants.h"

class Pitch;
class Paddle;
class Ball;
class Game;
class Controller;
namespace sf
{
	class Clock;
}

class Game : public sf::Drawable
{
public:
	enum class State
	{
		WAITING,
		ACTIVE,
	};

	Game();
	~Game();

	bool initialise(sf::Vector2f pitchSize);
	void update(float deltaTime);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void scoreGoal(Side side);

	State getState() const { return m_state; }
	const Pitch *getPitch() const { return m_pPitch.get(); }
	const Ball *getBall(int i) const { return m_pBall[i].get(); }
	const Paddle *getPaddle(Side side) const { return m_pPaddles[(int)side].get(); }

	void onKeyPressed(sf::Keyboard::Key key);
	void onKeyReleased(sf::Keyboard::Key key);

	sf::Clock clock;
	int m_score[2];

	int	m_numBalls;
	// AudioVisual m_audioVisual;

private:
	std::unique_ptr<Pitch> m_pPitch;
	std::unique_ptr<Ball> m_pBall[2];
	State m_state;
	std::unique_ptr<sf::Clock> m_pClock;

	std::unique_ptr<Paddle> m_pPaddles[2];
	std::unique_ptr<Controller> m_controllers[2];

	std::unique_ptr<sf::Shader> wobble;


	sf::Font m_font;
};
