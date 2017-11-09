#include "RectangleComponent.h"

namespace biemgine
{
    RectangleComponent::RectangleComponent(float width, float height, Color color)
        : color(color), width(width), height(height) {}

    RectangleComponent::~RectangleComponent() {}

    float RectangleComponent::getWidth() const {
        return width;
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

    ColorComponent RectangleComponent::getColor() const {
        return color;
    }
}
