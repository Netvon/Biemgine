#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using biemgine::bmComponent;

namespace spacebiem
{
    class bmAtmosphereComponent :
        public bmComponent
    {
    public:
        bmAtmosphereComponent(float offsetX, float offsetY, float r) :
            offsetX(offsetX), offsetY(offsetY), r(r)
        { };

        float getX() const;
        float getY() const;
        float getRadius() const;

    private:
        float offsetX, offsetY, r;
    };
}
