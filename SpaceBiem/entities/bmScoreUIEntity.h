#pragma once

#include "Biemgine.h"

using namespace biemgine;

namespace spacebiem
{
    class bmScoreUIEntity :
        public bmEntity
    {
    public:
        bmScoreUIEntity(float x = 20, float y = 30, float score = 0, string name = "Score");
    };
}
