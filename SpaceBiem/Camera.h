#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using std::string;
using biemgine::Component;

namespace spacebiem
{
    class Camera :
        public Component
    {
    public:
        Camera() : deltaX(0), deltaY(0){};
        ~Camera() {};

        inline float getDeltaX() const { return deltaX; };
        inline float getDeltaY() const { return deltaY; };
        inline int getWindowWidth() const { return windowWidth; };
        inline int getWindowHeight() const { return windowHeight; };

        inline void setDeltaX(float x)  { deltaX = x; };
        inline void setDeltaY(float y)  { deltaY = y; };
        inline void setWindowWidth(int width) { windowWidth = width; };
        inline void setWindowHeight(int height) { windowHeight = height; };

    private:
        float windowWidth;
        float windowHeight;

        float deltaX;
        float deltaY;
    };
}
