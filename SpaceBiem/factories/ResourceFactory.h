
#pragma once

#include "stdafx.h"

#include "EntityFactory.h"
#include "..\FileParser.h"
#include <vector>

using biemgine::Entity;
using biemgine::RandomGenerator;

namespace spacebiem
{
    class ResourceFactory :
        public EntityFactory
    {
    public:

        ~ResourceFactory() { };
        vector<Entity*> sceneStart(int windowW, int windowH) override;
        void sceneEnd(std::vector<Entity*> entities) override;


        vector<

    };
}
