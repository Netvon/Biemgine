#pragma once

#include "Biemgine.h"

using biemgine::Entity;
using biemgine::Color;

namespace spacebiem
{
    class PlayerEntity :
        public Entity
    {
    public:
        PlayerEntity(float x, float y, Color color, float w = -1, float h = -1, float mass = 1.0f, bool focused = true);
    };
}
