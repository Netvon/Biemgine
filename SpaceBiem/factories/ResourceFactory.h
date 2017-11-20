
#pragma once

#include "stdafx.h"

#include "EntityFactory.h"
#include "..\FileParser.h"
#include "..\entities\ResourceEntity.h"

#include <vector>
#include <math.h>

using biemgine::Entity;
using biemgine::EntityManager;
using biemgine::RandomGenerator;

namespace spacebiem
{
    class ResourceFactory :
        public EntityFactory
    {
    public:
        ResourceFactory();

        ~ResourceFactory() { };
        vector<Entity*> sceneStart(int windowW, int windowH) override;
        void sceneEnd(std::vector<Entity*> entities) override;
        void createPlanetResources(int x, int y, int r, string planet, std::shared_ptr<EntityManager> entityManager);
    private:

        map<string, map<string, vector<float>>> spawnRates;
        map<string, int> scores;
    };
}
