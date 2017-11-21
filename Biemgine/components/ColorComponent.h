#pragma once

#include "dlldef.h"
#include "Component.h"
#include "../primitives/Primitives.h"

namespace biemgine
{
    class BIEMGINE ColorComponent :
        public Component
    {
    public:
        ColorComponent(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
        ColorComponent(Color Color);

        ~ColorComponent();

        int getR() const;
        int getG() const;
        int getB() const;
        int getA() const;

        const Color& getColor() const;

    private:
        Color color;
    };
}
