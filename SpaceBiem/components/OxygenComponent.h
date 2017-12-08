#pragma once

#include "Biemgine.h"

using biemgine::Component;

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

        int getOxygenMax() const;

        int getOxygenScale() const;

    private:
        float oxygenAmount;
        int oxygenMax;
        int oxygenScale;
    };
}
