#pragma once

#include "Biemgine.h"
#include "../components/GravityComponent.h"
#include <vector>
#include <set>

using biemgine::System;
using biemgine::Vector;
using biemgine::Entity;
using biemgine::PhysicsComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::GroundedComponent;
using biemgine::PositionComponent;

namespace spacebiem
{
    class GravitySystem :
        public System
    {
    public:

        struct Entry {
            const Entity* entity;
            std::shared_ptr<PositionComponent> position;
            std::shared_ptr<PhysicsComponent> physics;
            std::shared_ptr<GroundedComponent> grounded;
            std::shared_ptr<AffectedByGravityComponent> affected;
            std::shared_ptr<GravityComponent> gravity;
        };

        void update(const Entity& entity) override;
        void after() override;

        void applyForceAndSetRotation(Vector& centerOfGravity, Vector& centerOfSatellite, std::shared_ptr<PhysicsComponent> satPhysics, std::shared_ptr<AffectedByGravityComponent> affected, std::shared_ptr<PositionComponent> satPosition);

    private:

        vector<Entry> satEntries;
        vector<Entry> gravEntries;

        set<int> added;
    };
}
