#pragma once

#include "stdafx.h"

#include "EntityFactory.h"
#include "..\FileParser.h"
#include <vector>

using biemgine::Entity;

namespace spacebiem
{
    class ScoreUIFactory :
        public EntityFactory
    {
    public:
        void sceneStart(int windowW, int windowH, shared_ptr<EntityManager> entityManager) override;
        void sceneEnd(std::vector<Entity*> entities) override;
    };
}
