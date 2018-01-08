#include "OxygenComponent.h"

namespace spacebiem
{
    float OxygenComponent::getOxygenAmount() const
    {
        return oxygenAmount;
    }

    void OxygenComponent::setIsGod(bool pIsGod)
    {
        isGod = pIsGod;
    }

    bool OxygenComponent::getIsGod() const
    {
        return isGod;
    }

    void OxygenComponent::setOxygenAmount(float pOxygen)
    {
        if (!isGod) {
            if (pOxygen >= 0.0f && pOxygen <= oxygenMax) {
                oxygenAmount = pOxygen;
            }
            else if (pOxygen <= 0.0f) {
                oxygenAmount = 0.0f;
            }
        }
    }

    void OxygenComponent::setAtmosphereEntity(std::shared_ptr<Entity> atmosphere)
    {
        currentAtmosphereEntity = atmosphere;
    }

    std::shared_ptr<Entity> OxygenComponent::getAtmosphereEntity() const
    {
        return currentAtmosphereEntity;
    }

    int OxygenComponent::getOxygenMax() const
    {
        return oxygenMax;
    }

    int OxygenComponent::getOxygenScale() const
    {
        return oxygenScale;
    }

}
