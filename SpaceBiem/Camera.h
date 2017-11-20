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
        Camera();
        ~Camera() {};

        float getDeltaX() const;
        float getDeltaY() const;
        int getWindowWidth() const;
        int getWindowHeight() const;

        void setDeltaX(float x);
        void setDeltaY(float y);
        void setWindowWidth(int width);
        void setWindowHeight(int height);

    private:
        float windowWidth;
        float windowHeight;

        float deltaX;
        float deltaY;
    };
}
