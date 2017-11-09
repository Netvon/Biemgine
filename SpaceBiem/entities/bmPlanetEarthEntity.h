#pragma once

#include "Biemgine.h"

using biemgine::bmEntity;
using biemgine::bmColor;

namespace spacebiem
{
    class bmPlanetEarthEntity :
        public bmEntity
    {
    public:
        bmPlanetEarthEntity(float x, float y, bmColor color, float w, float h);
    };
}
