#pragma once

#include "Biemgine.h"

using biemgine::Entity;
using biemgine::Color;

namespace spacebiem
{
    class PlanetToxicEntity :
        public Entity
    {
    public:
        PlanetToxicEntity(float x, float y, Color color, float w, float h, float atmosphere);
    };
}
