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
using biemgine::AnimatedTextureComponent;
using biemgine::TextureColumnDef;
using biemgine::TextureRowDef;

#include "../components/AIComponent.h"
#include "../globals/Functions.h"

namespace spacebiem
{
    AIEntity::AIEntity(float x, float y, Color color, float w, float h, float mass)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("color", new ColorComponent(color));
        addComponent("texture", new AnimatedTextureComponent("textures/PlayerSpriteSheet.png", 0, 0, TextureColumnDef{ 9llu, 128 }, TextureRowDef{ 1llu, 256 }, 7.5f / 2.0f, w, h, 5u, true, "background"));
        addComponent("physics", new PhysicsComponent(w, h, false, PhysicsComponentShape::RECTANGLE, mass));
        addComponent("grounded", new GroundedComponent);
        addComponent("affectedByGravity", new AffectedByGravityComponent(true));
        addComponent("collidable", new CollidableComponent(CollisionCategory::AI, CollisionCategory::PLAYER | CollisionCategory::PLANET));
        addComponent("ai", new AIComponent);

        addComponent<biemgine::ScriptComponent>("script", Functions::updateAnimatedBasesOnSpeed(this));

        setTag("ai");
    }
}
