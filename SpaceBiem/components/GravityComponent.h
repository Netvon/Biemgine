#pragma once

#include "Biemgine.h"

using biemgine::Component;

namespace spacebiem
{
    class GravityComponent :
        public Component
    {
    public:
        GravityComponent(float offsetX, float offsetY, float w, float h, float r) :
            offsetX(offsetX), offsetY(offsetY), w(w), h(h), r(r) {};

        float getX();
        float getY();
        float getWidth();
        float getHeight();
        float getRadius();

        constexpr static float getGravityConstant() {
            return 160.f;
        }

    private:
        float offsetX, offsetY, w, h, r;
    };
}
