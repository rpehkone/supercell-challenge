#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <thread>
#include <memory>
#include <array>

#include "MathUtils.h"
#include "Game.h"

void draw_visualizer(sf::RenderWindow& window, double freq[4])
{
	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color(0x41034480));

	float size = 50.0 * freq[0];
	rectangle.setSize(sf::Vector2f(window.getSize().x, -size));
	rectangle.setPosition(0, 0);
	window.draw(rectangle);

	size = 50.0 * freq[3];
	rectangle.setSize(sf::Vector2f(window.getSize().x, size));
	rectangle.setPosition(0, window.getSize().y);
	window.draw(rectangle);

/*
	size = 50.0 * freq[2];
	rectangle.setSize(sf::Vector2f(-size, window.getSize().y));
	rectangle.setPosition(0, 0);
	window.draw(rectangle);

	size = 50.0 * freq[3];
	rectangle.setSize(sf::Vector2f(size, window.getSize().y));
	rectangle.setPosition(window.getSize().x, 0);
	window.draw(rectangle);
*/
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

	AudioVisual audioViz = AudioVisual();
	// m_audioVisual = AudioVisual();
	audioViz.initialize();
	// m_audioVisual.getSampleOverFrequency();
	std::thread frequencyAnalyzationThread(&AudioVisual::getSampleOverFrequency, &audioViz);
	// std::this_thread::sleep_for(std::chrono::milliseconds(5000));



	// run the program as long as the window is open
	while (window.isOpen())
	{
		std::vector< std::vector <double> >& frequencyVisualizationVector = audioViz.getfrequencyVisualizationVector();
		double songPlayingOffset = audioViz.getSongPlayingOffset();
		int frequencyFrame = (int)(songPlayingOffset * 30);
		double this_freq[4] = {0,0,0,0};
		int freqBlockIdx = 2;
		for (int i = 0; i < 4; i++)
		{
			if (frequencyFrame < frequencyVisualizationVector.size())
				this_freq[i] = frequencyVisualizationVector[frequencyFrame][freqBlockIdx * i] * -1;
			this_freq[i] /= 150.0f;
			this_freq[i] = min(this_freq[i], 1.0f);
		}


		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// "close requested" event: we close the window
				window.close();
				exit(0);
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
		draw_visualizer(window, this_freq);

		window.draw(*pGame.get());
		window.display();
	}

	return 0;
}
