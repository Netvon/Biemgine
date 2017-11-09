#pragma once

#include "stdafx.h"
#include "Biemgine.h"

using std::string;
using biemgine::Entity;

namespace spacebiem
{
    class ScoreUIEntity :
        public Entity
    {
    public:
        ScoreUIEntity(float x = 20, float y = 30, float score = 0, const string& name = "Score");
    };
}
