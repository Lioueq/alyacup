#include <SFML/Graphics.hpp>
#include <string>
#include <optional>
#include "../include/gifController.hpp"


int main()
{
    alyatools::GifController gifController("../../images/tsukasa/");
    auto window = sf::RenderWindow(sf::VideoMode(gifController.getGifSize()), "giffy", sf::Style::None);
    window.setFramerateLimit(144);

    sf::Clock clock;
    bool isGrabbed = false;
    sf::Vector2i grabbedDelta;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    isGrabbed = true;
                    grabbedDelta = window.getPosition() - sf::Mouse::getPosition();
                }
                // if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
                //
                // }
            }
            if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (mouseButtonReleased->button == sf::Mouse::Button::Left)
                {
                    isGrabbed = false;
                }
            }
            if (event->is<sf::Event::MouseMoved>() && isGrabbed)
            {
                window.setPosition(sf::Mouse::getPosition() + grabbedDelta);
            }
        }
        if (clock.getElapsedTime().asMilliseconds() > 100)
        {
            gifController.nextTexture();
            clock.restart();
        }
        window.draw(gifController.getCurrentSprite());
        window.display();
    }
}