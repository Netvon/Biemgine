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
        PlanetEntity(float x, float y, Color color, float w, float h, const string& texture = "textures/earth-plain.png", const string& borderTexture = "textures/earth-TypeA.png", int pScoreBonus = 0, const string& pName="", bool scoreGiven = false);
        void createAtmosphere(float x, float y, float w, float h, float atmosphere = 1, bool shouldClouds = false, Color color = Color::White());
        void createScoreBonus(int pScoreBonus = 0, bool scoreGiven = false);
    };
}
