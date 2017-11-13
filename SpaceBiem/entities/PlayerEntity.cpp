#include "stdafx.h"
#include "PlayerEntity.h"

using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::TextureComponent;
using biemgine::PhysicsComponent;
using biemgine::GroundedComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PhysicsComponentShape;

#include "../components/OxygenComponent.h"
#include "../components/ScoreComponent.h"

namespace spacebiem
{
    PlayerEntity::PlayerEntity(float x, float y, Color color, float w, float h, float mass)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("color", new ColorComponent(color));
        addComponent("texture", new TextureComponent("textures/player-standing.png", 0, 0, w, h, 5u));
        addComponent("physics", new PhysicsComponent(w, h, false, PhysicsComponentShape::RECTANGLE, mass));
        addComponent("oxygen", new OxygenComponent);
        addComponent("grounded", new GroundedComponent(false));
        addComponent("score", new ScoreComponent);
        addComponent("affectedByGravity", new AffectedByGravityComponent(true));
    }
}