#pragma once

#include "Biemgine.h"

using biemgine::Color;

#include "PlanetEntity.h"

namespace spacebiem
{
    class PlanetEarthEntity :
        public PlanetEntity
    {
    public:
        PlanetEarthEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere, const string& pName = "", bool scoreGiven = false, const string& border = "textures/earth-TypeA.png");
    };
}
