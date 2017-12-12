#pragma once

#include "Biemgine.h"

using biemgine::Color;

#include "AIEntity.h"

namespace spacebiem
{
    class MummieAIEntity :
        public AIEntity
    {
    public:
        MummieAIEntity(float x, float y, Color color, float w = -1, float h = -1, float mass = 1.0f);
    };
}
