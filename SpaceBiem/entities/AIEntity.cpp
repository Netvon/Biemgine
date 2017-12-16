#include "stdafx.h"
#include "AIEntity.h"

using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::AnimatedTextureComponent;
using biemgine::PhysicsComponent;
using biemgine::GroundedComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::TextureColumnDef;
using biemgine::TextureRowDef;
using biemgine::PhysicsComponentShape;
using biemgine::CollidableComponent;
using biemgine::AnimatedTextureComponent;
using biemgine::TextureColumnDef;
using biemgine::TextureRowDef;

#include "../components/AIComponent.h"
#include "../globals/Functions.h"

namespace spacebiem
{
    AIEntity::AIEntity(float x, float y, Color color, float w, float h, float mass, const std::string animatedTexture, size_t textureCount, bool pCanIdle, bool pCanWander, bool pCanFollow)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("color", new ColorComponent(color));
        addComponent("texture", new AnimatedTextureComponent(animatedTexture, 0, 0, TextureColumnDef{ textureCount, 256 }, TextureRowDef{ 1llu, 256 }, 7.5f / 2.0f, w, h, 5u, true, "background"));
        addComponent("physics", new PhysicsComponent(w, h, false, PhysicsComponentShape::RECTANGLE, mass));
        addComponent("grounded", new GroundedComponent);
        addComponent("affectedByGravity", new AffectedByGravityComponent(true));
        addComponent("collidable", new CollidableComponent(CollisionCategory::AI, CollisionCategory::PLAYER | CollisionCategory::PLANET));
        addComponent("ai", new AIComponent(pCanIdle, pCanWander, pCanFollow));

        addComponent<biemgine::ScriptComponent>("script", Functions::updateAnimatedBasesOnSpeed(getComponent<GroundedComponent>("grounded"), getComponent<AnimatedTextureComponent>("texture"), getComponent<PhysicsComponent>("physics")));

        setTag("ai");
    }
}
