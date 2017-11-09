#pragma once

#include "Biemgine.h"

using biemgine::bmComponent;

namespace spacebiem
{
    class bmGravityComponent :
        public bmComponent
    {
    public:
        bmGravityComponent(float offsetX, float offsetY, float w, float h, float r) :
            offsetX(offsetX), offsetY(offsetY), w(w), h(h), r(r) {};

        float getX();
        float getY();
        float getWidth();
        float getHeight();
        float getRadius();

    private:
        float offsetX, offsetY, w, h, r;
    };
}
