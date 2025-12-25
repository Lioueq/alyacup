#include <SFML/Graphics.hpp>
#include <iostream>

std::string formatNumber(int n) {
    std::string s = "";
    s += std::to_string(n);
    while (s.size() != 4) {
        s = "0" + s;
    }
    return s;
}

int main()
{
    sf::Image img("../../images/tsukasa/c68fd3c377f7cc6ed90cbea037483692-0001.jpg");
    sf::Vector2u windowSize = img.getSize();
    std::vector<sf::Texture> frames;
    for (int i = 1; i <= 26; ++i) {
       std::string path = "../../images/tsukasa/c68fd3c377f7cc6ed90cbea037483692-" + formatNumber(i) + ".jpg";
       sf::Texture texture(path);
       frames.push_back(texture);
    }
    auto window = sf::RenderWindow(sf::VideoMode(windowSize), "giffy", sf::Style::None);
    window.setFramerateLimit(144);

    int currentFrame = 0;
    sf::Sprite sprite(frames[currentFrame]);
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
            currentFrame = (currentFrame + 1) % frames.size();
            sprite.setTexture(frames[currentFrame]);
            clock.restart();
        }
        window.draw(sprite);
        window.display();
    }
}