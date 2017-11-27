#pragma once
#include "Biemgine.h"
#include "factories\ResourceFactory.h"
#include "components\ScoreComponent.h"
#include "components\OxygenComponent.h"
#include "components\ResourceComponent.h"

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
