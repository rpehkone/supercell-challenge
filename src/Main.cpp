#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <memory>

#include "Game.h"

void draw_wobble(sf::RenderTarget &target, sf::RenderStates states)
{
}

int main()
{
	bool sRgb = false;

	sf::Image icon;
	icon.loadFromFile("assets/pong_icon.jpg");
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	contextSettings.sRgbCapable = sRgb;
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Pong", sf::Style::Titlebar | sf::Style::Close);

	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("assets/background_art.png"))
	{
		std::cout << "failed to load background";
		exit(-1);
	}
	backgroundTexture.setSmooth(true);
	sf::Sprite background(backgroundTexture);

	std::unique_ptr<Game> pGame = std::make_unique<Game>();
	if (!pGame->initialise(window.getView().getSize()))
	{
		std::cerr << "Game Failed to initialise" << std::endl;
		return 1;
	}

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// "close requested" event: we close the window
				window.close();
				break;
			case sf::Event::KeyPressed:
				pGame->onKeyPressed(event.key.code);
				break;
			case sf::Event::KeyReleased:
				pGame->onKeyReleased(event.key.code);
				break;
			default:
				break;
			}
		}

		sf::Time elapsedTime = pGame->clock.getElapsedTime();
		pGame->clock.restart();
		pGame->update(elapsedTime.asSeconds());

		// clear the window with black color
		window.clear(sf::Color::Black);

		sf::Vector2f winsize = (sf::Vector2f)window.getView().getSize();
		winsize.x /= background.getLocalBounds().width;
		winsize.y /= background.getLocalBounds().height;
		background.setScale(winsize);
		window.draw(background);

		window.draw(*pGame.get());
		window.display();
	}

	return 0;
}
