#pragma once

#include "stdafx.h"
#include "Biemgine.h"

using biemgine::Entity;
using biemgine::Color;
using std::string;

namespace spacebiem
{
    class PlanetEntity :
        public Entity
    {
    public:
        PlanetEntity(float x, float y, Color color, float w, float h, string texture = "textures/earth-plain.png", string borderTexture = "textures/earth-TypeA.png", int pScoreBonus = 0);
        void createAtmosphere(float x, float y, float w, float h, float atmosphere = 1, string texture = "textures/atmosphere.png", bool shouldClouds = false);
        void createScoreBonus(int pScoreBonus = 0);
    };
}
