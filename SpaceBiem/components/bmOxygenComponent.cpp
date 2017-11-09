#include "stdafx.h"
#include "bmOxygenComponent.h"

namespace spacebiem
{
    int bmOxygenComponent::getOxygenAmount() const
    {
        return oxygenAmount;
    }

    void bmOxygenComponent::setOxygenAmount(int pOxygen)
    {
        if (pOxygen >= 0 && pOxygen <= oxygenMax) {
            oxygenAmount = pOxygen;
        }
    }

    int bmOxygenComponent::getOxygenMax() const
    {
        return oxygenMax;
    }

    int bmOxygenComponent::getOxygenDecrease() const
    {
        return oxygenDecrease;
    }

    int bmOxygenComponent::getOxygenIncrease() const
    {
        return oxygenIncrease;
    }
}
