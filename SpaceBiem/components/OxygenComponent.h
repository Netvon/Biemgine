#pragma once

#include "Biemgine.h"
#include "../components/AtmosphereComponent.h"

using biemgine::Component;
using biemgine::Entity;

namespace spacebiem
{
    class OxygenComponent :
        public Component
    {
    public:
        OxygenComponent(int pOxygenMax = 2000, int oxygenScale = 1) :
            oxygenAmount(pOxygenMax),
            oxygenMax(pOxygenMax),
            oxygenScale(oxygenScale)
        {};

        float getOxygenAmount() const;
        void setOxygenAmount(float pOxygen);

        void setAtmosphereEntity(std::shared_ptr<Entity> atmosphere);
        std::shared_ptr<Entity> getAtmosphereEntity() const;

        int getOxygenMax() const;

        int getOxygenScale() const;

    private:
        float oxygenAmount;
        int oxygenMax;
        int oxygenScale;
        std::shared_ptr<Entity> currentAtmosphereEntity = nullptr;;
    };
}
