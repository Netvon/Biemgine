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
        ~ResourceUISystem() {};

        void update(const Entity& entity) override;

    private:
        std::map<std::shared_ptr<ResourceComponent>, bool> resourceMap;
    };
}
