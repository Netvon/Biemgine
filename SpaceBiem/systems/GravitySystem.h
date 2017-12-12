#pragma once

#include "Biemgine.h"
#include <vector>

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
        void update(const Entity& entity) override;
        void after() override;

        void applyForceAndSetRotation(Vector& centerOfGravity, Vector& centerOfSatellite, std::shared_ptr<PhysicsComponent> satPhysics, std::shared_ptr<AffectedByGravityComponent> affected, std::shared_ptr<PositionComponent> satPosition);

    private:
        vector<const Entity*> gravityPoints;
        vector<const Entity*> satellites;
    };
}
