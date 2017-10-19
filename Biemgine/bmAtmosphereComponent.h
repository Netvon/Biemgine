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
    {};

    float getX() {
        return offsetX;
    }

    float getY() {
        return offsetY;
    }

    float getRadius() {
        return r;
    }

private:
    float offsetX, offsetY, r;

};

