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

        ~OxygenSystem() {};

        void update(const Entity& entity) override;
    private:
        vector<Entity> entitiesWithAtmospheres;

    };
}
