#pragma once

#include "stdafx.h"
#include "Biemgine.h"

using std::string;
using biemgine::bmEntity;

namespace spacebiem
{
    class bmScoreUIEntity :
        public bmEntity
    {
    public:
        bmScoreUIEntity(float x = 20, float y = 30, float score = 0, const string& name = "Score");
    };
}
