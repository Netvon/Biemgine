#pragma once

#include "Biemgine.h"

using biemgine::System;
using biemgine::Entity;
using biemgine::PhysicsComponent;
using biemgine::Vector;

namespace spacebiem
{
    class MovementSystem :
        public System
    {
    public:
        void update(const Entity& entity) override;

        // Inherited via System
        virtual required_components requirements() const override;
    };
}
