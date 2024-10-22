#pragma once

#include "stdafx.h"

#include "EntityFactory.h"
#include "..\FileParser.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\PlanetSandEntity.h"
#include "..\entities\PlanetToxicEntity.h"
#include "..\entities\PlanetLavaEntity.h"
#include "..\entities\PlanetIceEntity.h"
#include "..\entities\WormholeEntity.h"
#include "ResourceFactory.h"
#include "NameGenerator.h"
#include <vector>

using biemgine::Entity;
using biemgine::EntityManager;
using biemgine::RandomGenerator;
using biemgine::TextComponent;
using biemgine::PositionComponent;
using biemgine::TextureComponent;

namespace spacebiem
{
    class PlanetFactory
    {
    public:
        ~PlanetFactory() {};
        void create(const string& type, int pX, int pY, int width, int height, std::shared_ptr<EntityManager> entityManager, ResourceFactory resourceFactory, NameGenerator nameGenerator, map<string, float> atmosphereM, map<string, int> scoreBonus);
        void load(const string& type, int pX, int pY, int width, int height, std::shared_ptr<EntityManager> entityManager, string name, map<string, float> atmosphereM, int planetScore, bool isDiscovered, vector<float> flagComponent);
    };
}
