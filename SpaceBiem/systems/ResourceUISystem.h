#pragma once

#include "Biemgine.h"
#include "..\components\ResourceComponent.h"
#include "..\components\ResourceBonusComponent.h"

using biemgine::System;
using biemgine::Entity;
using biemgine::TextComponent;
using biemgine::PositionComponent;
using biemgine::UIComponent;
using biemgine::ColorComponent;

namespace spacebiem
{
    class ResourceUISystem : public System
    {
    public:
        struct PlayerEntry
        {
            Entity* entity;
            std::shared_ptr<ResourceComponent> resourceComponent;
        };

        struct ResourceTextEntry
        {
            Entity* entity;
            std::shared_ptr<ResourceBonusComponent> resourceBonusComponent;
            std::shared_ptr<ColorComponent> colorComponent;
            std::shared_ptr<TextComponent> textComponent;
        };

        ~ResourceUISystem() {};

        void onAddEntity(Entity& entity) override;
        void update() override;

    private:
        vector<PlayerEntry> playerEntries;
        vector<ResourceTextEntry> resourceTextEntries;
    };
}
