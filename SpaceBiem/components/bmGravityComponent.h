#pragma once

#include "stdafx.h"

using namespace biemgine;

class bmGravityComponent :
    public bmComponent
{
public:
    bmGravityComponent(float offsetX, float offsetY, float w, float h, float r) : offsetX(offsetX), offsetY(offsetY), w(w), h(h), r(r) {};

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

    float getRadius() {
        return r;
    }

private:
    float offsetX, offsetY, w, h, r;
};

