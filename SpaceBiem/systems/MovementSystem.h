#pragma once

#include "Biemgine.h"

using biemgine::System;
using biemgine::Entity;

namespace spacebiem
{
    class MovementSystem :
        public System
    {
    public:
        void update(const Entity& entity) override;
        void onSceneSwitch() override { };
    };
}
