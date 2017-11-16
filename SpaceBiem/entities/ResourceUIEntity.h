#pragma once

#include "Biemgine.h"

using biemgine::Entity;
using biemgine::Color;

namespace spacebiem
{
    class ResourceUIEntity :
        public Entity
    {
    public:
        ResourceUIEntity(float x, float y, Color color, std::string resourceName);
    };
}
