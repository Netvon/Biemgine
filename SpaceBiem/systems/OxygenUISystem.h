#pragma once

#include "Biemgine.h"
#include "..\components\OxygenComponent.h"

using biemgine::System;
using biemgine::GraphicsDevice;
using biemgine::Entity;
using std::map;

namespace spacebiem
{
    class OxygenUISystem
        : public System
    {
    public:
        ~OxygenUISystem() {};

        void update(const Entity& entity) override;

    private:
        map<std::shared_ptr<OxygenComponent>, bool> oxygenMap;
    };
}
