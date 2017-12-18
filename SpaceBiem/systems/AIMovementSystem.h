#pragma once

#include "stdafx.h"
#include <vector>
using std::vector;

#include "Biemgine.h"

using biemgine::System;
using biemgine::Entity;

using biemgine::PositionComponent;
using biemgine::GroundedComponent;
using biemgine::AnimatedTextureComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PhysicsComponent;

#include "../entities/AIEntity.h"
#include "../components/AIComponent.h"
#include "../entities/PlayerEntity.h"

namespace spacebiem
{
    struct AIEntry
    {
        Entity * entity;
        std::shared_ptr<PositionComponent> position;
        std::shared_ptr<GroundedComponent> grounded;
        std::shared_ptr<AffectedByGravityComponent> affectedByGravity;
        std::shared_ptr<AnimatedTextureComponent> animatedTexture;
        std::shared_ptr<PhysicsComponent> physics;
        std::shared_ptr<AIComponent> ai;
    };

    struct PlayerEntry
    {
        Entity * entity;
        std::shared_ptr<PositionComponent> positionComponent;
    };

    class AIMovementSystem :
        public System
    {
    public:
        void onAddEntity(Entity & entity) override;
        void update() override;

    private:
        vector<AIEntry> aiEntries;
        vector<PlayerEntry> playerEntries;

        const Entity * findPlayerInRange(const Entity * entity) const;
        Direction computeDirection() const;
        float computeForce() const;
    };
}
