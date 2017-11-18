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

        float getDeltaX() const { return deltaX; };
        float getDeltaY() const { return deltaY; };

        void setDeltaX(float x)  { deltaX = x; };
        void setDeltaY(float y)  { deltaY = y; };

    private:
        float deltaX;
        float deltaY;
    };
}
