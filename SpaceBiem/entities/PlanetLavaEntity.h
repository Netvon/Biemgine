#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using biemgine::Color;

#include "PlanetEntity.h"

namespace spacebiem
{
    class PlanetLavaEntity :
        public PlanetEntity
    {
    public:
        PlanetLavaEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere, string pName = "");
    };
}
