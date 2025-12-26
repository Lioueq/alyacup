#include "../include/gifController.hpp"
#include <filesystem>
#include <optional>
#include <string>


namespace fs = std::filesystem;

namespace alyatools {
    GifController::GifController(std::string path) : currentFrame(0) {
        if (fs::exists(path) && fs::is_directory(path)) {
            for (const auto& entry : fs::directory_iterator(path)) {
                if (fs::is_regular_file(entry.status())) {
                    if (frames.size() == 0) {
                        sf::Image img(path + entry.path().filename().string());
                        windowSize = img.getSize();
                    }
                    sf::Texture texture(path + entry.path().filename().string());
                    frames.push_back(texture);
                }
            }
            sprite.emplace(frames[currentFrame]);
        }
    }

    sf::Vector2u GifController::getGifSize() const {
        return windowSize;
    }

    sf::Sprite GifController::getCurrentSprite() {
        return sprite.value();
    }

    void GifController::nextTexture() {
        currentFrame = (currentFrame + 1) % frames.size();
        sprite->setTexture(frames[currentFrame]);
    }

    std::string formatNumber(int n) {
        std::string s = std::to_string(n);
        while (s.size() != 4) {
            s = "0" + s;
        }
        return s;
    }
}

