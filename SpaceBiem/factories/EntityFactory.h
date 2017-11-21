#pragma once

#include "stdafx.h"
#include "Biemgine.h"
#include <vector>

using biemgine::Entity;

namespace spacebiem
{
    class EntityFactory
    {
    public:
        virtual vector<Entity*> sceneStart(int windowWidth, int windowH) = 0;
        virtual void sceneEnd(std::vector<Entity*> entities) = 0;
    };
}
