#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using biemgine::Entity;
using biemgine::PositionComponent;
using biemgine::TextureComponent;
using biemgine::PhysicsComponent;
using biemgine::ColorComponent;
using biemgine::GroundComponent;

#pragma once

#include "../components/GravityComponent.h"

using biemgine::Color;

namespace spacebiem
{
    class PlanetMoonEntity :
        public Entity
    {
    public:
        PlanetMoonEntity(float x, float y, Color color, float w, float h);
    };
}
