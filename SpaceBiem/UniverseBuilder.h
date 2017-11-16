#pragma once
#include "Biemgine.h"

using biemgine::Entity;

namespace spacebiem
{
    class UniverseBuilder
    {
    public:
        UniverseBuilder();
        void build(int windowW, int windowH, vector<Entity*>& placeIn);
    };
}
