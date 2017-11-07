#pragma once

#include "bmComponent.h"
#include "../primitives/bmPrimitives.h"

namespace biemgine
{
    class bmColorComponent :
        public bmComponent
    {
    public:
        bmColorComponent::bmColorComponent(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
            : color({ r, g, b, a }) {}

        bmColorComponent::bmColorComponent(bmColor bmColor)
            : color(bmColor) {}

        int getR() const { return color.r; };
        int getG() const { return color.g; };
        int getB() const { return color.b; };
        int getA() const { return color.a; };

        bmColor getColor() const { return color; }

    private:
        bmColor color;
    };
}
