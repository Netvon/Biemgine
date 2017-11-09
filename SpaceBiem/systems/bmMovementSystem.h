#pragma once

#include "Biemgine.h"
using namespace biemgine;

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
