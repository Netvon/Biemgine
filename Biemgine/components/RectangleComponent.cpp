#include "RectangleComponent.h"

namespace biemgine
{
    RectangleComponent::RectangleComponent(float width, float height, Color color)
        : color(color), originalColor(color), width(width), originalWidth(width), height(height) {}

    RectangleComponent::~RectangleComponent() {}

    float RectangleComponent::getWidth() const {
        return width;
    }

    float RectangleComponent::getOriginalWidth() const
    {
        return originalWidth;
    }

    float RectangleComponent::getHeight() const {
        return height;
    }

    void RectangleComponent::setWidth(float pWidth) {
        width = pWidth;
    }

    void RectangleComponent::setHeight(float pHeight) {
        height = pHeight;
    }

    void RectangleComponent::setColor(Color pColor)
    {
        color = pColor;
    }

    ColorComponent RectangleComponent::getColor() const {
        return color;
    }

    ColorComponent RectangleComponent::getOriginalColor() const
    {
        return originalColor;
    }
}
