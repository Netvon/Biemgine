#pragma once

#include "Biemgine.h"
#include "components\PositionComponent.h"
#include "stdafx.h"

using biemgine::Component;
using biemgine::PositionComponent;

namespace spacebiem
{
    class AtmosphereComponent :
        public Component
    {
    public:
        AtmosphereComponent(std::shared_ptr<PositionComponent> pc, float offsetX, float offsetY, float r, float oxygenModifier) :
            pc(pc), offsetX(offsetX), offsetY(offsetY), r(r), oxygenModifier(oxygenModifier)
        { };

        std::shared_ptr<PositionComponent> pc = nullptr;

        float getX() const;
        float getY() const;
        float getRadius() const;
        float getOxygenModifier() const;

    private:
        float offsetX, offsetY, r, oxygenModifier;
    };
}
