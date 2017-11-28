#pragma once

#include "Biemgine.h"

using biemgine::System;
using biemgine::Entity;

namespace spacebiem
{
    class AIMovementSystem :
        public System
    {
    public:
        void update(const Entity & entity) override;
    };
}
