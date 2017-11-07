#pragma once
#include "bmPositionComponent.h"
#include "bmColorComponent.h"

namespace biemgine
{
    class bmRectangleComponent :
        public bmComponent
    {
    public:
        bmRectangleComponent(float width, float height, bmColor color)
            : color(color), width(width), height(height) { }

        float getWidth() const {
            return width;
        }

        float getHeight() const {
            return height;
        }

        void setWidth(float pWidth) {
            width = pWidth;
        }

        void setHeight(float pHeight) {
            height = pHeight;
        }

        bmColorComponent getColor() const {
            return color;
        }

    private:
        float width, height;
        bmColorComponent color;
    };
}
