#pragma once

#include "Biemgine.h"

using biemgine::Color;

#include "AIEntity.h"
#include "../components/AIComponent.h"

namespace spacebiem
{
    class SnowmanAIEntity :
        public AIEntity
    {
    public:
        SnowmanAIEntity(float x, float y, Color color, float w = -1, float h = -1, float mass = 1.0f);
    };
}
