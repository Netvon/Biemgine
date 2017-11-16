#pragma once

#include "..\components\OxygenComponent.h"
#include "..\scenes\GameoverScene.h"
#include "..\components\ResourceComponent.h"
#include "..\components\ScoreComponent.h"

#include "Biemgine.h"
#include <vector>

using biemgine::System;
using biemgine::Entity;

namespace spacebiem
{
    class GameoverSystem :
        public System
    {
    public:

        GameoverSystem() {};
        ~GameoverSystem() {};

        void update(const Entity& entity) override;
        void onSceneSwitch() override {};

        
    private:

    };
}
