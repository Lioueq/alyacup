#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <optional>

namespace alya {
    std::string formatNumber(int n);

    class GifController {
    public:
        GifController(std::string path);

        sf::Vector2u getGifSize() const;

        sf::Sprite getCurrentSprite();

        void nextTexture();

    private:
        std::vector<sf::Texture> frames;
        std::optional<sf::Sprite> sprite;
        int currentFrame;
        sf::Vector2u windowSize;
    };
}