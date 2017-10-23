#pragma once

#include "bmComponent.h"

class bmAtmosphereComponent :
    public bmComponent
{
public:
    bmAtmosphereComponent(float offsetX, float offsetY, float r) :
        offsetX(offsetX),
        offsetY(offsetY),
        r(r)
    { };

    float getX() const {
        return offsetX;
    }

    float getY() const {
        return offsetY;
    }

    float getRadius() const {
        return r;
    }

private:
    float offsetX, offsetY, r;
};

