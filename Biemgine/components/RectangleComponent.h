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
        float getOriginalWidth() const;
        void setWidth(float pWidth);
        void setHeight(float pHeight);
        void setColor(Color pColor);
        ColorComponent getColor() const;
        ColorComponent getOriginalColor() const;

    private:
        float width, height, originalWidth;
        ColorComponent color, originalColor;
    };
}
