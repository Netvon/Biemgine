#pragma once

#include "Biemgine.h"
#include "..\components\OxygenComponent.h"

using biemgine::System;
using biemgine::GraphicsDevice;
using biemgine::Entity;
using std::map;

namespace spacebiem
{
    class OxygenUISystem : public System
    {
    public:

        OxygenUISystem() {};
        ~OxygenUISystem() {};

        void OxygenUISystem::setGraphicsDevice(GraphicsDevice* graphicsDevice);

        void before(const float deltaTime) override;
        void update(const Entity& entity, const float deltaTime) override;
        void after(const float deltaTime) override;

        void onSceneSwitch() override;

    private:
        GraphicsDevice* graphicsDevice = nullptr;

        map<OxygenComponent*, bool> oxygenMap;

    };
}
