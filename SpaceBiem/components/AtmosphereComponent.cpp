#include "Biemgine.h"
#include "AtmosphereComponent.h"

namespace spacebiem
{
	float AtmosphereComponent::getX() const
	{
		if (pc != nullptr)
		{
			return offsetX + pc->getX();
		}

		return offsetX;
	}

	float AtmosphereComponent::getY() const
	{
		if (pc != nullptr)
		{
			return offsetY + pc->getY();
		}

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
