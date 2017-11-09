#include "bmRectangleComponent.h"

namespace biemgine
{
    bmRectangleComponent::bmRectangleComponent(float width, float height, bmColor color)
        : color(color), width(width), height(height) {}

    bmRectangleComponent::~bmRectangleComponent() {}

    float bmRectangleComponent::getWidth() const {
        return width;
    }

    float bmRectangleComponent::getHeight() const {
        return height;
    }

    void bmRectangleComponent::setWidth(float pWidth) {
        width = pWidth;
    }

    void bmRectangleComponent::setHeight(float pHeight) {
        height = pHeight;
    }

    bmColorComponent bmRectangleComponent::getColor() const {
        return color;
    }
}
