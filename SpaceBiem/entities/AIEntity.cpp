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

#include "../components/AIComponent.h"
#include "../globals/Functions.h"

namespace spacebiem
{
    AIEntity::AIEntity(float x, float y, Color color, float w, float h, float mass, const std::string animatedTexture, size_t textureCount, bool pCanIdle, bool pCanWander, bool pCanFollow, std::initializer_list<AnimationDef> pAnimationDefs)
    {
        addComponent<PositionComponent>("position", x, y);
        addComponent<ColorComponent>("color", color);
        addComponent<AnimatedTextureComponent>("texture", animatedTexture, 0, 0, pAnimationDefs, "walk", 7.5f / 2.0f, w, h, 5u, true, "background");
        addComponent<PhysicsComponent>("physics", w, h, false, PhysicsComponentShape::RECTANGLE, mass);
        addComponent<GroundedComponent>("grounded");
        addComponent<AffectedByGravityComponent>("affectedByGravity", true);
        addComponent<CollidableComponent>("collidable", CollisionCategory::AI, CollisionCategory::PLAYER | CollisionCategory::PLANET);
        addComponent<AIComponent>("ai", pCanIdle, pCanWander, pCanFollow);

        addComponent<biemgine::ScriptComponent>("script",
            Functions::updateAnimatedBasesOnSpeed(
                getComponent<GroundedComponent>("grounded"),
                getComponent<AnimatedTextureComponent>("texture"),
                getComponent<PhysicsComponent>("physics")));

        setTag("ai");
    }
}
