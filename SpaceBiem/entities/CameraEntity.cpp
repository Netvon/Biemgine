#include "stdafx.h"
#include "CameraEntity.h"

using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::AnimatedTextureComponent;
using biemgine::PhysicsComponent;
using biemgine::GroundedComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PhysicsComponentShape;
using biemgine::CollidableComponent;
using biemgine::TextureColumnDef;
using biemgine::AnimationDef;
using biemgine::TextureRowDef;
using biemgine::CameraComponent;

#include "../components/OxygenComponent.h"
#include "../components/ScoreComponent.h"
#include "../components/ResourceComponent.h"
#include "../components/MovementComponent.h"
#include "../globals/Functions.h"

namespace spacebiem
{
    CameraEntity::CameraEntity(float x, float y, string onlyMoveSuffix)
    {
        addComponent("position", new PositionComponent(x, y));
        
        addComponent("camera", new CameraComponent(onlyMoveSuffix));

        setTag("camera");
    }
}
