#pragma once

#include "bmComponent.h"
#include "../primitives/bmPrimitives.h"

using primitives::bmColor;

namespace components
{
    class bmColorComponent :
        public components::bmComponent
    {
    public:
        bmColorComponent::bmColorComponent(int r, int g, int b, int a = 255)
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
