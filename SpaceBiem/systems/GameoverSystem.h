#pragma once

#include "..\components\OxygenComponent.h"
#include "..\scenes\GameoverScene.h"
#include "..\components\ResourceComponent.h"
#include "..\components\ScoreComponent.h"
#include "..\components\ScoreBonusComponent.h"

#include "Biemgine.h"
#include <vector>

using biemgine::System;
using biemgine::Entity;
using biemgine::CollidableComponent;

namespace spacebiem
{
    class GameoverSystem :
        public System
    {
    public:
        ~GameoverSystem() {};

        void update(const Entity& entity) override;
    };
}
