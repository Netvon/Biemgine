#pragma once

#include "Biemgine.h"
#include "..\components\GravityComponent.h"
#include "..\components\MovementComponent.h"

using biemgine::System;
using biemgine::Entity;
using biemgine::GroundedComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PositionComponent;
using biemgine::PhysicsComponent;
using biemgine::AnimatedTextureComponent;
using biemgine::Vector;

namespace spacebiem
{
    class JumpSystem :
        public System
    {
    public:
        struct PlayerEntry
        {
            Entity* entity;
            std::shared_ptr<PositionComponent> positionComponent;
            std::shared_ptr<GroundedComponent> groundedComponent;
            std::shared_ptr<AffectedByGravityComponent> affectedByGravityComponent;
            std::shared_ptr<PhysicsComponent> physicsComponent;
            std::shared_ptr<AnimatedTextureComponent> animatedComponent;
            std::shared_ptr<MovementComponent> movementComponent;
        };

        void onAddEntity(Entity& entity) override;
        void update() override;

    private:
        vector<PlayerEntry> playerEntries;
    };
}
