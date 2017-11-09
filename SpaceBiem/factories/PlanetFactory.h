#pragma once

#include "stdafx.h"

#include "EntityFactory.h"
#include "..\FileHandler.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\PlanetSandEntity.h"
#include "..\entities\PlanetToxicEntity.h"
#include <vector>

using biemgine::Entity;
using biemgine::RandomGenerator;

namespace spacebiem
{
    class PlanetFactory :
        public EntityFactory
    {
    public:

        ~PlanetFactory() { };
        vector<Entity*> sceneStart(int windowW, int windowH) override;
        void sceneEnd(std::vector<Entity*> entities) override;
    };
}
