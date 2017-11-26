#pragma once

#include "stdafx.h"
#include "Biemgine.h"
#include <vector>
#include <memory>

using biemgine::Entity;
using biemgine::EntityManager;
using std::shared_ptr;

namespace spacebiem
{
    class EntityFactory
    {
    public:
        virtual void sceneStart(int windowWidth, int windowH, shared_ptr<EntityManager> entityManager) = 0;
        virtual void sceneEnd(shared_ptr<EntityManager> entityManager) = 0;
    };
}
