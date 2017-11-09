#include "Biemgine.h"
#include "bmSurfaceEntity.h"

using biemgine::bmPositionComponent;
using biemgine::bmRectangleComponent;
using biemgine::bmPhysicsComponent;
using biemgine::PhysicsComponentShape;

namespace spacebiem
{
    bmSurfaceEntity::bmSurfaceEntity(float x, float y, bmColor color, float w, float h)
    {
        addComponent("position", new bmPositionComponent(x, y));
        addComponent("rectangle", new bmRectangleComponent(w, h, color));
        addComponent("physics", new bmPhysicsComponent(w, h, true, PhysicsComponentShape::RECTANGLE));
    }
}
