//
// Created by abs on 27.12.2025.
//

#include "../include/tools.hpp"
#include "SFML/Graphics.hpp"

namespace alya::tools {
    void transformImage(sf::Image& img) {
        unsigned int width = img.getSize().x;
        unsigned int height = img.getSize().y;
        for (unsigned int i = 0; i < width; ++i) {
            for (unsigned int j = 0; j < height; ++j) {
                sf::Color color = img.getPixel({i, j});
                color.r = ~color.r;
                color.g = ~color.g;
                color.b = ~color.b;
                img.setPixel({i, j}, color);
            }
        }
    }
}