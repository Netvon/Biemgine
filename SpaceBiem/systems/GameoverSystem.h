#pragma once

#include "..\components\OxygenComponent.h"
#include "..\scenes\GameoverScene.h"
#include "..\components\ResourceComponent.h"
#include "..\components\ScoreComponent.h"
#include "..\components\ScoreBonusComponent.h"
#include "..\scenes\LevelLoadScene.h"

#include "Biemgine.h"
#include <vector>

using biemgine::System;
using biemgine::Entity;
using biemgine::CollidableComponent;
using biemgine::GroundedComponent;
using biemgine::PositionComponent;

namespace spacebiem
{
    class GameoverSystem :
        public System
    {
    public:

        GameoverSystem(bool customLevel = false): customLevel(customLevel) {};

        struct PlayerEntry
        {
            Entity* entity;
            std::shared_ptr<PositionComponent> positionComponent;
            std::shared_ptr<GroundedComponent> groundedComponent;
            std::shared_ptr<OxygenComponent> oxygenComponent;
            std::shared_ptr<ScoreComponent> scoreComponent;
            std::shared_ptr<ResourceComponent> resourceComponent;
            std::shared_ptr<CollidableComponent> collidableComponent;
        };

        ~GameoverSystem() {};

        void onAddEntity(Entity& entity) override;
        void update() override;

    private:
        vector<PlayerEntry> playerEntries;
        bool customLevel;
    };
}
