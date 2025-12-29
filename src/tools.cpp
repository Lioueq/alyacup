//
// Created by abs on 27.12.2025.
//

#include "../include/tools.hpp"
#include "SFML/Graphics.hpp"

namespace alya::tools {
    void transformImage(sf::Image& img) {
        unsigned int width = img.getSize().x;
        unsigned int height = img.getSize().y;
        sf::Color targetColor = sf::Color::White;
        unsigned int tolerance = 10;
        for (unsigned int i = 0; i < width; ++i) {
            for (unsigned int j = 0; j < height; ++j) {
                sf::Color pixel = img.getPixel({i, j});
                if (std::abs(pixel.r - targetColor.r) < tolerance &&
                    std::abs(pixel.g - targetColor.g) < tolerance &&
                    std::abs(pixel.b - targetColor.b) < tolerance)
                    {
                        img.setPixel({i, j}, sf::Color(0, 0, 0, 0));
                    }
            }
        }
    }

    void transparentImage(sf::Image& img) {
        img.createMaskFromColor(sf::Color::White);
    }
}