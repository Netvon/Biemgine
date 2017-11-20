#pragma once

#include "Biemgine.h"

using biemgine::Component;

namespace spacebiem
{
    class OxygenComponent :
        public Component
    {
    public:
        OxygenComponent(float pOxygenMax = 1000, int oxygenScale = 1) :
            oxygenAmount(pOxygenMax),
            oxygenMax(pOxygenMax),
            oxygenScale(oxygenScale)
        {};

        float getOxygenAmount() const;
        void setOxygenAmount(float pOxygen);

        float getOxygenMax() const;

        int getOxygenScale() const;

    private:
        float oxygenAmount;
        float oxygenMax;
        int oxygenScale;
    };
}
