#pragma once

#include "Biemgine.h"
using biemgine::System;
using biemgine::Entity;

#include "..\components\AtmosphereComponent.h"
#include "..\components\OxygenComponent.h"
#include "..\scenes\MenuScene.h"

namespace spacebiem
{
    class OxygenSystem : public System
    {
    public:
        void update(const Entity& entity) override;
        void before() override;
        void after() override;
    private:
        vector<Entity> entitiesWithAtmospheres;
        vector<Entity> entitiesWithOxygen;
        std::shared_ptr<Entity> currentAtmosphereEntity = nullptr;
    };
}
