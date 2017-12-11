#include "stdafx.h"
#include "PlayerEntity.h"

using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::AnimatedTextureComponent;
using biemgine::PhysicsComponent;
using biemgine::GroundedComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PhysicsComponentShape;
using biemgine::CollidableComponent;
using biemgine::TextureColumnDef;
using biemgine::TextureRowDef;
using biemgine::CameraComponent;

#include "../components/OxygenComponent.h"
#include "../components/ScoreComponent.h"
#include "../components/ResourceComponent.h"
#include "../components/MovementComponent.h"

namespace spacebiem
{
    PlayerEntity::PlayerEntity(float x, float y, Color color, float w, float h, float mass, bool focused)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("color", new ColorComponent(color));
        addComponent("texture", new AnimatedTextureComponent("textures/PlayerSpriteSheet.png", 0, 0, TextureColumnDef{ 9llu, 128 }, TextureRowDef{ 1llu, 256 }, 7.5f / 2.0f, w, h, 5u, true, "background"));
        addComponent("physics", new PhysicsComponent(w, h, false, PhysicsComponentShape::RECTANGLE, mass));
        addComponent("oxygen", new OxygenComponent);
        addComponent("grounded", new GroundedComponent);
        addComponent("score", new ScoreComponent);
        addComponent("affectedByGravity", new AffectedByGravityComponent(true));
        addComponent("resources", new ResourceComponent);
        addComponent("collidable", new CollidableComponent(CollisionType::PLAYER, CollisionType::PLANET | CollisionType::AI | CollisionType::PLAYER | CollisionType::RESOURCE));
        addComponent("movement", new MovementComponent);
        if(focused) addComponent("camera", new CameraComponent);

        setTag("player");
    }
}
