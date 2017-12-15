#pragma once

#include "Biemgine.h"

using biemgine::System;
using biemgine::Entity;

using biemgine::PositionComponent;
using biemgine::CollidableComponent;
using biemgine::AudioComponent;

#include "..\components\AtmosphereComponent.h"
#include "..\components\OxygenComponent.h"
#include "..\scenes\MenuScene.h"

namespace spacebiem
{
    class OxygenSystem : public System
    {
    public:
        struct PlayerEntry
        {
            Entity* entity;
            std::shared_ptr<PositionComponent> positionComponent;
            std::shared_ptr<OxygenComponent> oxygenComponent;
            std::shared_ptr<CollidableComponent> collidableComponent;
        };

        struct PlanetEntry
        {
            Entity* entity;
            std::shared_ptr<PositionComponent> positionComponent;
            std::shared_ptr<AtmosphereComponent> AtmosphereComponent;
            std::shared_ptr<AudioComponent> audioComponent;
            
        };

        void onAddEntity(Entity& entity) override;
        void update() override;
    private:

        std::shared_ptr<PlanetEntry> currentPlanetEntry = nullptr;
        vector<PlayerEntry> playerEntries;
        vector<PlanetEntry> planetEntries;
    };
}
