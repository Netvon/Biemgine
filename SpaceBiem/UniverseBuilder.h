#pragma once
#include "Biemgine.h"

using biemgine::EntityManager;
using biemgine::RandomGenerator;
using biemgine::Entity;

namespace spacebiem
{
    class UniverseBuilder
    {
    public:
        UniverseBuilder();
        void build(int windowW, int windowH, std::shared_ptr<EntityManager> entityManager);
    };
}
