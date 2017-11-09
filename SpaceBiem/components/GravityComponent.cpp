#include "Biemgine.h"
#include "GravityComponent.h"

namespace spacebiem
{
    float GravityComponent::getX() {
        return offsetX;
    }

    float GravityComponent::getY() {
        return offsetY;
    }

    float GravityComponent::getWidth() {
        return w;
    }

    float GravityComponent::getHeight() {
        return h;
    }

    float GravityComponent::getRadius() {
        return r;
    }
}
