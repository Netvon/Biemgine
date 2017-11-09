#pragma once

#include "Biemgine.h"

using biemgine::bmSystem;
using biemgine::bmEntity;

namespace spacebiem
{
    class bmMovementSystem :
        public bmSystem
    {
    public:
        void update(const bmEntity& entity) override;
        void onSceneSwitch() override { };
    };
}
