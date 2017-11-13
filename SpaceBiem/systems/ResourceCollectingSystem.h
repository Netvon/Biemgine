#pragma once

#include "Biemgine.h"
using biemgine::System;
using biemgine::Entity;


namespace spacebiem
{
    class ResourceCollectingSystem : public System
    {
    public:

        ResourceCollectingSystem() {};
        ~ResourceCollectingSystem() {};

        void before() override;
        void update(const Entity& entity) override;
        void after() override;

        void onSceneSwitch() override;

    private:

    };
}
