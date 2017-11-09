#pragma once

#include "Biemgine.h"
using biemgine::bmEntity;
using biemgine::bmColor;

namespace spacebiem
{
    class bmSurfaceEntity :
        public bmEntity
    {
    public:
        bmSurfaceEntity(float x, float y, bmColor color, float w, float h);
    };
}
