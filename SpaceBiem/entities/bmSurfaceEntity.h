#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using namespace biemgine;

namespace spacebiem
{
    class bmSurfaceEntity :
        public bmEntity
    {
    public:
        bmSurfaceEntity(float x, float y, bmColor color, float w, float h)
        {
            addComponent("position", new bmPositionComponent(x, y));
            addComponent("rectangle", new bmRectangleComponent(w, h, color));
            addComponent("physics", new bmPhysicsComponent(w, h, true, RECTANGLE));
        }
    };
}
