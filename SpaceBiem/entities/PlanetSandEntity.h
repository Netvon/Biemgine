#pragma once

#include "Biemgine.h"

using biemgine::Entity;
using biemgine::Color;

namespace spacebiem
{
    class PlanetSandEntity :
        public Entity
    {
    public:
        PlanetSandEntity(float x, float y, Color color, float w, float h, float atmosphere);
    };
}
