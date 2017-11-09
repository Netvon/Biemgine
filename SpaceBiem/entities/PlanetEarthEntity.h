#pragma once

#include "Biemgine.h"

using biemgine::Entity;
using biemgine::Color;

namespace spacebiem
{
    class PlanetEarthEntity :
        public Entity
    {
    public:
        PlanetEarthEntity(float x, float y, Color color, float w, float h, float atmosphere);
    };
}
