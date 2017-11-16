#pragma once

#include "Biemgine.h"
#include "..\components\ResourceComponent.h"

using biemgine::GraphicsDevice;
using biemgine::System;
using biemgine::Entity;

namespace spacebiem
{
    class ResourceUISystem : public System
    {
    public:
        ResourceUISystem() {};
        ~ResourceUISystem() {};

        void ResourceUISystem::setGraphicsDevice(GraphicsDevice* graphicsDevice);

        void before(const float deltaTime) override;
        void update(const Entity& entity, const float deltaTime) override;
        void after(const float deltaTime) override;

        void onSceneSwitch() override;

    private:
        GraphicsDevice* graphicsDevice = nullptr;

        std::map<ResourceComponent*, bool> resourceMap;
    };
}
