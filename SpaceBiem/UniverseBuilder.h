#pragma once
#include "Biemgine.h"
#include "factories\ResourceFactory.h"

using biemgine::EntityManager;
using biemgine::RandomGenerator;
using biemgine::Entity;

namespace spacebiem
{
    class UniverseBuilder
    {
    public:
        UniverseBuilder();
        void build(std::shared_ptr<EntityManager> entityManager);
    };
}
