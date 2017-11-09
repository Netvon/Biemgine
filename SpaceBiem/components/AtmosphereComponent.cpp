#include "Biemgine.h"
#include "AtmosphereComponent.h"

namespace spacebiem
{
    float AtmosphereComponent::getX() const
    {
        return offsetX;
    }

    float AtmosphereComponent::getY() const
    {
        return offsetY;
    }

    float AtmosphereComponent::getRadius() const
    {
        return r;
    }
	float AtmosphereComponent::getOxygenModifier() const
	{
		return oxygenModifier;
	}
}
