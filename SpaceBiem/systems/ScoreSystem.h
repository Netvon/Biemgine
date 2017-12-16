#pragma once

#include "Biemgine.h"

using biemgine::System;
using biemgine::Entity;
using biemgine::GroundedComponent;
using biemgine::CollidableComponent;
using biemgine::TextureComponent;
using biemgine::TextComponent;
using biemgine::PositionComponent;

namespace spacebiem
{
    class ScoreSystem :
        public System
    {
    public:
        struct PlayerEntry
        {
            Entity* entity;
            std::shared_ptr<PositionComponent> positionComponent;
            std::shared_ptr<GroundedComponent> groundedComponent;
            std::shared_ptr<ScoreComponent> scoreComponent;
        };

        void onAddEntity(Entity& entity) override;
        void update() override;

    private: 
        vector<PlayerEntry> playerEntries;
    };
}
