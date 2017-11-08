#include "bmColorComponent.h"

namespace biemgine {
    bmColorComponent::bmColorComponent(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        : color({ r, g, b, a }) { }
    bmColorComponent::bmColorComponent(bmColor bmColor)
        : color(bmColor) {}

    bmColorComponent::~bmColorComponent() {}

    int bmColorComponent::getR() const { return color.r; }
    int bmColorComponent::getG() const { return color.g; }
    int bmColorComponent::getB() const { return color.b; }
    int bmColorComponent::getA() const { return color.a; }
    const bmColor & bmColorComponent::getColor() const { return color; }
}
