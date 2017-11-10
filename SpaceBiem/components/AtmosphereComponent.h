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
        AtmosphereComponent(float offsetX, float offsetY, float r, float oxygenModifier) :
            offsetX(offsetX), offsetY(offsetY), r(r), oxygenModifier(oxygenModifier)
        { };

        float getX() const;
        float getY() const;
        float getRadius() const;
        float getOxygenModifier() const;

    private:
        float offsetX, offsetY, r, oxygenModifier;
    };
}
