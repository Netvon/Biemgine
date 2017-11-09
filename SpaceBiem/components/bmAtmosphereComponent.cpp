#include "Biemgine.h"
#include "bmAtmosphereComponent.h"

namespace spacebiem
{
    float bmAtmosphereComponent::getX() const
    {
        return offsetX;
    }

    float bmAtmosphereComponent::getY() const
    {
        return offsetY;
    }

    float bmAtmosphereComponent::getRadius() const
    {
        return r;
    }
}
