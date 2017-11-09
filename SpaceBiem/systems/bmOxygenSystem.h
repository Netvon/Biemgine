#pragma once

#include "Biemgine.h"
using namespace biemgine;

#include "..\components\bmAtmosphereComponent.h"
#include "..\components\bmOxygenComponent.h"

namespace spacebiem
{
    class bmOxygenSystem : public bmSystem
    {
    public:

        bmOxygenSystem() {};
        ~bmOxygenSystem() {};

        void before() override;
        void update(const bmEntity& entity) override;
        void after() override;

        void onSceneSwitch() override;


    private:
        vector<bmAtmosphereComponent*> atmospheres;

    };
}
