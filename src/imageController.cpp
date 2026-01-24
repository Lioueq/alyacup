#include "../include/imageController.h"

#include <stdexcept>

using namespace Gdiplus;

namespace alyacup::tools {
    ImageController::ImageController(const wchar_t* path) {
        img = new Image(path);
        if (img->GetLastStatus() != Ok) {
            delete img;
            img = nullptr;
            throw std::runtime_error("load image error");
        }
        frameCount = img->GetFrameCount(&FrameDimensionTime);
        if (frameCount == 0) {
            frameCount = 1;
        }
        currentFrame = 1;
        w = img->GetWidth();
        h = img->GetHeight();
    }

    ImageController::~ImageController() {
        delete img;
    }

    Image* ImageController::getImage() const {
        return img;
    }

    void ImageController::nextFrame() {
        currentFrame = (currentFrame + 1) % frameCount;
        img->SelectActiveFrame(&FrameDimensionTime, currentFrame);
    }
}
