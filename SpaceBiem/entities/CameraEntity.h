#pragma once

#include "Biemgine.h"

using biemgine::Entity;
using biemgine::Color;

namespace spacebiem
{
    class CameraEntity :
        public Entity
    {
    public:
        CameraEntity(float x, float y, string onlyMoveSuffix = "");
    };
}
