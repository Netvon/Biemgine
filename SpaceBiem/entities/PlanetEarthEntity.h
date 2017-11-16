#pragma once

#include "Biemgine.h"

using biemgine::Color;

#include "PlanetEntity.h"

namespace spacebiem
{
    class PlanetEarthEntity :
        public PlanetEntity
    {
    public:
        PlanetEarthEntity(float x, float y, Color color, float w, float h, float atmosphere);
    };
}
