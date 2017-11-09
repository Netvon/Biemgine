#include "Biemgine.h"
#include "bmGravityComponent.h"

namespace spacebiem
{
    float bmGravityComponent::getX() {
        return offsetX;
    }

    float bmGravityComponent::getY() {
        return offsetY;
    }

    float bmGravityComponent::getWidth() {
        return w;
    }

    float bmGravityComponent::getHeight() {
        return h;
    }

    float bmGravityComponent::getRadius() {
        return r;
    }
}
