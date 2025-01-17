
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
    class ResourceFactory
    {
    public:
        ResourceFactory();

        ~ResourceFactory() { };
        void generatePlanetResources(int x, int y, int r, string planet, std::shared_ptr<EntityManager> entityManager);
        void createPlanetResources(float x, float y, int w, int h, string name, std::shared_ptr<EntityManager> entityManager);
    private:

        map<string, map<string, vector<float>>> spawnRates;
        map<string, int> scores;
    };
}
