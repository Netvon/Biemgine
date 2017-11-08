#pragma once

#include "dlldef.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"

namespace biemgine
{
    class BIEMGINE bmRectangleComponent :
        public bmComponent
    {
    public:
        bmRectangleComponent(float width, float height, bmColor color);
        ~bmRectangleComponent();

        float getWidth() const;
        float getHeight() const;
        void setWidth(float pWidth);
        void setHeight(float pHeight);
        bmColorComponent getColor() const;

    private:
        float width, height;
        bmColorComponent color;
    };
}
