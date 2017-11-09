#include "ColorComponent.h"

namespace biemgine
{
    ColorComponent::ColorComponent(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        : color({ r, g, b, a }) { }
    ColorComponent::ColorComponent(Color Color)
        : color(Color) {}

    ColorComponent::~ColorComponent() {}

    int ColorComponent::getR() const { return color.r; }
    int ColorComponent::getG() const { return color.g; }
    int ColorComponent::getB() const { return color.b; }
    int ColorComponent::getA() const { return color.a; }
    const Color & ColorComponent::getColor() const { return color; }
}
