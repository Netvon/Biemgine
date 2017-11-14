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
        vector<Entity*> sceneStart(int windowW, int windowH) override;
        void sceneEnd(std::vector<Entity*> entities) override;
    };
}
