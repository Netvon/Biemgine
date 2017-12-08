#pragma once
#include "Biemgine.h"
#include "..\factories\ResourceFactory.h"
#include "..\factories\PlanetFactory.h"
#include "..\components\ScoreComponent.h"
#include "..\components\OxygenComponent.h"
#include "..\components\ResourceComponent.h"

#include "..\FileParser.h"
#include "..\entities\PlayerEntity.h"

using biemgine::Entity;
using biemgine::PhysicsComponent;
using biemgine::PositionComponent;

using biemgine::EntityManager;
using biemgine::RandomGenerator;
using biemgine::Entity;

namespace spacebiem
{
    class UniverseBuilder
    {
    public:
        UniverseBuilder();
        void build(std::shared_ptr<EntityManager> entityManager, bool newGame = true);
    };
}
