#include "Biemgine.h"
#include "SurfaceEntity.h"

using biemgine::PositionComponent;
using biemgine::RectangleComponent;
using biemgine::PhysicsComponent;
using biemgine::PhysicsComponentShape;

namespace spacebiem
{
    SurfaceEntity::SurfaceEntity(float x, float y, Color color, float w, float h)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("rectangle", new RectangleComponent(w, h, color));
        addComponent("physics", new PhysicsComponent(w, h, true, PhysicsComponentShape::RECTANGLE));
    }
}
