#pragma once

#include "..\components\OxygenComponent.h"
#include "..\scenes\GameoverScene.h"
#include "..\components\ResourceComponent.h"
#include "..\components\ScoreComponent.h"
#include "..\components\ScoreBonusComponent.h"
#include "..\components\ResourceBonusComponent.h"

#include "..\globals\Difficulty.h"

#include "Biemgine.h"
#include <vector>

using biemgine::System;
using biemgine::Entity;
using biemgine::CollidableComponent;
using biemgine::GroundedComponent;
using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::TextComponent;

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

        struct ResourceTextEntry
        {
            Entity* entity;
            std::shared_ptr<ResourceBonusComponent> resourceBonusComponent;
            std::shared_ptr<ColorComponent> colorComponent;
            std::shared_ptr<TextComponent> textComponent;
        };

        struct ResourceTextureEntry
        {
            Entity* entity;
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
            challenging["metal"] = 100;
            challenging["diamond"] = 20;
            challenging["uranium"] = 10;
            challenging["anti-matter"] = 0;

            map<string, int> expert;
            expert["metal"] = 200;
            expert["diamond"] = 40;
            expert["uranium"] = 20;
            expert["anti-matter"] = 1;

            winConditions[Difficulty::NORMAL] = normal;
            winConditions[Difficulty::CHALLENING] = challenging;
            winConditions[Difficulty::EXPERT] = expert;
        };

        ~WinSystem() {};

        void onAddEntity(Entity& entity) override;
        void update() override;

    private:
        vector<PlayerEntry> playerEntries;
        vector<ResourceTextEntry> resourceTextEntries;
        vector<ResourceTextureEntry> resourceTextureEntries;

        map<Difficulty ,map<string, int>> winConditions;

        Difficulty difficulty;
    };
}

