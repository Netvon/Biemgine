#pragma once

#include "Biemgine.h"
using biemgine::System;
using biemgine::Entity;

namespace spacebiem
{
    class ScoreSystem :
        public System
    {
    public:
        ScoreSystem();
        ~ScoreSystem();

        void update(const Entity& entity) override;
        void onSceneSwitch() override;
    };
}
