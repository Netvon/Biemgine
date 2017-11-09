#pragma once

#include "Biemgine.h"
#include "..\components\ScoreComponent.h"

using biemgine::GraphicsDevice;
using biemgine::System;
using biemgine::Entity;

namespace spacebiem
{
    class ScoreUISystem : public System
    {
    public:
        ScoreUISystem() {};
        ~ScoreUISystem() {};

        void ScoreUISystem::setGraphicsDevice(GraphicsDevice* graphicsDevice);

        void before(const float deltaTime) override;
        void update(const Entity& entity, const float deltaTime) override;
        void after(const float deltaTime) override;

        void onSceneSwitch() override;

    private:
        GraphicsDevice* graphicsDevice = nullptr;

        std::map<ScoreComponent*, bool> scoreMap;
    };
}
