//
// Created by abss on 23.01.2026.
//

#ifndef ALYACUP_IMAGECONTROLLER_H
#define ALYACUP_IMAGECONTROLLER_H

#include <windows.h>
#include <gdiplus.h>

using namespace Gdiplus;

namespace alyacup::tools {
    class ImageController {
    public:
        ImageController(const wchar_t* path);
        ~ImageController();

        Image* getImage() const;

        void nextFrame();

        UINT frameCount;

    private:
        Image* img;
        UINT currentFrame;
    };
}


#endif //ALYACUP_IMAGECONTROLLER_H