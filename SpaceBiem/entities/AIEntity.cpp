#include "stdafx.h"
#include "AIEntity.h"

using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::TextureComponent;
using biemgine::PhysicsComponent;
using biemgine::GroundedComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PhysicsComponentShape;
using biemgine::CollidableComponent;

#include "../components/AIComponent.h"

namespace spacebiem
{
    AIEntity::AIEntity(float x, float y, Color color, float w, float h, float mass)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("color", new ColorComponent(color));
        addComponent("texture", new TextureComponent("textures/player-standing.png", 0, 0, w, h, 5u, true, "background"));
        addComponent("physics", new PhysicsComponent(w, h, false, PhysicsComponentShape::RECTANGLE, mass));
        addComponent("grounded", new GroundedComponent);
        addComponent("affectedByGravity", new AffectedByGravityComponent(true));
        addComponent("collidable", new CollidableComponent);
        addComponent("ai", new AIComponent);

        setTag("ai");
    }
}
