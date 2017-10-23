#pragma once

#include "bmComponent.h"

class bmGravityComponent :
    public bmComponent
{
public:
    bmGravityComponent(float offsetX, float offsetY, float w, float h) : offsetX(offsetX), offsetY(offsetY), w(w), h(h) {};

    float getX() {
        return offsetX;
    }

    float getY() {
        return offsetY;
    }

    float getWidth() {
        return w;
    }

    float getHeight() {
        return h;
    }

private:
    float offsetX, offsetY, w, h;
};

