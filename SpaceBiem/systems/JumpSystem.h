#pragma once

#include "Biemgine.h"
#include "..\components\GravityComponent.h"

using biemgine::System;
using biemgine::Entity;
using biemgine::GroundedComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PositionComponent;
using biemgine::PhysicsComponent;
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
        };

        void onAddEntity(Entity& entity) override;
        void update() override;

    private:
        vector<PlayerEntry> playerEntries;
    };
}
