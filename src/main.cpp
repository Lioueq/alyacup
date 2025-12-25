#include <SFML/Graphics.hpp>
#include <iostream>
#include <format>

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
       std::cout << path << '\n';
       sf::Texture texture(path);
       frames.push_back(texture);
    }
    auto window = sf::RenderWindow(sf::VideoMode(windowSize), "giffy", sf::Style::None);
    window.setFramerateLimit(144);

    int currentFrame = 0;
    sf::Sprite sprite(frames[currentFrame]);
    sf::Clock clock;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        if (clock.getElapsedTime().asMilliseconds() > 100)
        {
            currentFrame = (currentFrame + 1) % frames.size();
            sprite.setTexture(frames[currentFrame]);
            clock.restart();
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}
