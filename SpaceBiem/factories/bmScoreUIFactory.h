#pragma once

#include "stdafx.h"

#include "bmEntityFactory.h"
#include "..\bmFileHandler.h"
#include <vector>

using biemgine::bmEntity;

namespace spacebiem
{
    class bmScoreUIFactory :
        public bmEntityFactory
    {
    public:
        vector<bmEntity*> sceneStart(int windowW, int windowH) override;
        void sceneEnd(std::vector<bmEntity*> entities) override;
    };
}
