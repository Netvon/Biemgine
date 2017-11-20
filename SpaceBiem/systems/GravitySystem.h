#pragma once

#include "Biemgine.h"
#include <vector>

using biemgine::System;
using biemgine::Vector;
using biemgine::Entity;
using biemgine::PhysicsComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::GroundedComponent;

namespace spacebiem
{
    class GravitySystem :
        public System
    {
    public:
        void update(const Entity& entity) override;
        void after() override;

        void applyForce(Vector centerOfGravity, Vector centerOfSatellite, PhysicsComponent * satPhysics, AffectedByGravityComponent* affected);

        void onSceneSwitch() override {};

    private:
        vector<const Entity*> gravityPoints;
        vector<const Entity*> satellites;
    };
}
