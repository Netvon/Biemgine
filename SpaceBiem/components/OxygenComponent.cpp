#include "OxygenComponent.h"

namespace spacebiem
{
    float OxygenComponent::getOxygenAmount() const
    {
        return oxygenAmount;
    }

    void OxygenComponent::setOxygenAmount(float pOxygen)
    {
        if (pOxygen >= 0 && pOxygen <= oxygenMax) {
            oxygenAmount = pOxygen;
        }
    }

    float OxygenComponent::getOxygenMax() const
    {
        return oxygenMax;
    }

    int OxygenComponent::getOxygenScale() const
    {
        return oxygenScale;
    }

}
