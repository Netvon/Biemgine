#pragma once

#include "stdafx.h"
#include "Biemgine.h"
#include <vector>

using biemgine::bmEntity;

namespace spacebiem
{
    class bmEntityFactory
    {
    public:
        virtual vector<bmEntity*> sceneStart(int windowWidth, int windowH) = 0;
        virtual void sceneEnd(std::vector<bmEntity*> entities) = 0;
    };
}
