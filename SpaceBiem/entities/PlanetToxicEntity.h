#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using biemgine::Color;
using biemgine::ColorComponent;

#include "PlanetEntity.h"

namespace spacebiem
{
    class PlanetToxicEntity :
        public PlanetEntity
    {
    public:
        PlanetToxicEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere, string pName="");
    };
}
