#pragma once

#include "Biemgine.h"
using biemgine::System;
using biemgine::Entity;

#include "..\components\AtmosphereComponent.h"
#include "..\components\OxygenComponent.h"

namespace spacebiem
{
    class OxygenSystem : public System
    {
    public:

        OxygenSystem() {};
        ~OxygenSystem() {};

        void before() override;
        void update(const Entity& entity) override;
        void after() override;

        void onSceneSwitch() override;


    private:
        vector<AtmosphereComponent*> atmospheres;

    };
}
