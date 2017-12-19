#pragma once

#include "Biemgine.h"
#include "..\components\OxygenComponent.h"

using biemgine::System;
using biemgine::Entity;
using biemgine::Color;
using biemgine::UIComponent;
using biemgine::PositionComponent;
using biemgine::TextureComponent;
using std::map;

namespace spacebiem
{
    class OxygenUISystem
        : public System
    {
    public:
        struct OxygenEntry
        {
            Entity* entity;
            std::shared_ptr<OxygenComponent> oxygenComponent;

        };

        struct TextureEntry
        {
            Entity* entity;
            vector<std::shared_ptr<TextureComponent>> textureComponents;

        };

        ~OxygenUISystem() {};

        void onAddEntity(Entity& entity) override;
        void update() override;

    private:
        vector<OxygenEntry> oxygenEntries;
        vector<TextureEntry> textureEntries;
    };
}
