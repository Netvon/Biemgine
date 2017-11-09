#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using biemgine::Component;

namespace spacebiem
{
    class AtmosphereComponent :
        public Component
    {
    public:
        AtmosphereComponent(float offsetX, float offsetY, float r) :
            offsetX(offsetX), offsetY(offsetY), r(r)
        { };

        float getX() const;
        float getY() const;
        float getRadius() const;

    private:
        float offsetX, offsetY, r;
    };
}
