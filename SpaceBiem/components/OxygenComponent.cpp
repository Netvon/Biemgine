#include "OxygenComponent.h"

namespace spacebiem
{
    int OxygenComponent::getOxygenAmount() const
    {
        return oxygenAmount;
    }

    void OxygenComponent::setOxygenAmount(int pOxygen)
    {
        if (pOxygen >= 0 && pOxygen <= oxygenMax) {
            oxygenAmount = pOxygen;
        }
    }

    int OxygenComponent::getOxygenMax() const
    {
        return oxygenMax;
    }

    int OxygenComponent::getOxygenDecrease() const
    {
        return oxygenDecrease;
    }

    int OxygenComponent::getOxygenIncrease() const
    {
        return oxygenIncrease;
    }
}
