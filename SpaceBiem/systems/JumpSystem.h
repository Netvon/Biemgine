#pragma once

#include "Biemgine.h"

using biemgine::System;
using biemgine::Entity;

namespace spacebiem
{
    class JumpSystem :
        public System
    {
    public:
        void update(const Entity& entity) override;

        // Inherited via System
        virtual required_components requirements() const override;
    };
}
