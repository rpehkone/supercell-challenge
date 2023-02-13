#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Game.h"
#include <memory>
#include <iostream>

void draw_wobble(sf::RenderTarget &target, sf::RenderStates states)
{

}

int main()
{
    bool sRgb = false;

    // Request a 24-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.sRgbCapable = sRgb;
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Pong 3");
    window.setKeyRepeatEnabled(false);
    
    // Create a sprite for the background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/texture.jpg"))
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
            switch(event.type)
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
