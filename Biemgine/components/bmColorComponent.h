#pragma once

#include "dlldef.h"
#include "bmComponent.h"
#include "../primitives/bmPrimitives.h"

namespace biemgine
{
    class BIEMGINE bmColorComponent :
        public bmComponent
    {
    public:
        bmColorComponent(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
        bmColorComponent(bmColor bmColor);

        ~bmColorComponent();

        int getR() const;
        int getG() const;
        int getB() const;
        int getA() const;

        const bmColor& getColor() const;

    private:
        bmColor color;
    };
}
