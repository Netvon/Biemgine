#pragma once

#include "Biemgine.h"
#include "..\components\ScoreComponent.h"

using biemgine::GraphicsDevice;
using biemgine::System;
using biemgine::Entity;
using biemgine::TextComponent;
using biemgine::PositionComponent;
using biemgine::UIComponent;
using biemgine::Color;

namespace spacebiem
{
    class ScoreUISystem : public System
    {
    public:
        struct PlayerEntry
        {
            Entity* entity;
            std::shared_ptr<ScoreComponent> scoreComponent;
        };

        struct ScoreUIEntry
        {
            Entity* entity;
            std::shared_ptr<ScoreComponent> scoreComponent;
            std::shared_ptr<TextComponent> textComponent;
        };

        ~ScoreUISystem() {};

        void onAddEntity(Entity& entity) override;
        void update() override;
        void update(const Entity& entity) override;

    private:
        vector<PlayerEntry> playerEntries;
        vector<ScoreUIEntry> scoreUIEntries;
        std::map<std::shared_ptr<ScoreComponent>, bool> scoreMap;
    };
}
