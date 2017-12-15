#pragma once

#include "biemgine.h"
using biemgine::System;
using biemgine::Entity;
using biemgine::CollidableComponent;
using biemgine::AudioComponent;

#include "../components/ResourceComponent.h"
#include "../components/ResourceBonusComponent.h"
#include "../components/ScoreBonusComponent.h"
#include "../components/ScoreComponent.h"


namespace spacebiem
{
    class ResourceCollectingSystem : public System
    {
    public:
        struct PlayerEntry
        {
            Entity* entity;
            std::shared_ptr<CollidableComponent> collidableComponent;
            std::shared_ptr<ResourceComponent> resourceComponent;
            std::shared_ptr<ScoreComponent> scoreComponent;

        };

        void onAddEntity(Entity& entity) override;
        void update();

    private:
        vector<PlayerEntry> playerEntries;
    };
}
