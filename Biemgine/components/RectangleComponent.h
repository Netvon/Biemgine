#pragma once

#include "dlldef.h"
#include "PositionComponent.h"
#include "ColorComponent.h"

namespace biemgine
{
    class BIEMGINE RectangleComponent :
        public Component
    {
    public:
        RectangleComponent(float width, float height, Color color);
        ~RectangleComponent();

        float getWidth() const;
        float getHeight() const;
        void setWidth(float pWidth);
        void setHeight(float pHeight);
        ColorComponent getColor() const;

    private:
        float width, height;
        ColorComponent color;
    };
}
