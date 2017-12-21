#pragma once

#include "..\components\OxygenComponent.h"
#include "..\scenes\LevelScene.h"
#include "..\components\ScoreComponent.h"
#include "..\components\MovementComponent.h"
#include "..\components\ScoreBonusComponent.h"

#include "Biemgine.h"
#include <vector>

using biemgine::System;
using biemgine::Entity;

namespace spacebiem
{
    class CheatSystem :
        public System
    {
    public:
        struct PlayerEntry
        {
            Entity* entity;
            std::shared_ptr<OxygenComponent> oxygenComponent;
            std::shared_ptr<ScoreComponent> scoreComponent;
            std::shared_ptr<MovementComponent> movementComponent;
        };

        ~CheatSystem() {};

        void onAddEntity(Entity& entity) override;
        void update() override;

    private:
        vector<PlayerEntry> playerEntries;
    };
}
