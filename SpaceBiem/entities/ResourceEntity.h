#pragma once

#include "Biemgine.h"

using biemgine::Entity;
using biemgine::Color;

namespace spacebiem
{
    class ResourceEntity :
        public Entity
    {
    public:
        ResourceEntity(float x, float y, Color color, float w = -1, float h = -1, string rName="", int scoreBonus=0);
    };
}
