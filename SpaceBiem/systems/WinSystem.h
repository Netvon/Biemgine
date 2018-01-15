#pragma once

#include "..\components\OxygenComponent.h"
#include "..\scenes\GameoverScene.h"
#include "..\components\ResourceComponent.h"
#include "..\components\ScoreComponent.h"
#include "..\components\ScoreBonusComponent.h"

#include "..\globals\Difficulty.h"

#include "Biemgine.h"
#include <vector>

using biemgine::System;
using biemgine::Entity;
using biemgine::CollidableComponent;
using biemgine::GroundedComponent;
using biemgine::PositionComponent;

namespace spacebiem
{
    class WinSystem :
        public System
    {
    public:
        struct PlayerEntry
        {
            Entity* entity;
            std::shared_ptr<PositionComponent> positionComponent;
            std::shared_ptr<GroundedComponent> groundedComponent;
            std::shared_ptr<ResourceComponent> resourceComponent;
            std::shared_ptr<CollidableComponent> collidableComponent;
        };

        WinSystem(Difficulty pDifficulty) :
            difficulty(pDifficulty)
        {
            map<string, int> normal;
            normal["metal"] = 50;
            normal["diamond"] = 10;
            normal["uranium"] = 0;
            normal["anti-matter"] = 0;

            map<string, int> challenging;
            normal["metal"] = 100;
            normal["diamond"] = 20;
            normal["uranium"] = 10;
            normal["anti-matter"] = 0;

            map<string, int> expert;
            normal["metal"] = 200;
            normal["diamond"] = 40;
            normal["uranium"] = 20;
            normal["anti-matter"] = 1;

            winConditions[Difficulty::NORMAL] = normal;
            winConditions[Difficulty::CHALLENING] = challenging;
            winConditions[Difficulty::EXPERT] = expert;
        };

        ~WinSystem() {};

        void onAddEntity(Entity& entity) override;
        void update() override;

    private:
        vector<PlayerEntry> playerEntries;

        map<Difficulty ,map<string, int>> winConditions;

        Difficulty difficulty;
    };
}

