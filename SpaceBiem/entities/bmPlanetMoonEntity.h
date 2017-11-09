#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using biemgine::bmEntity;
using biemgine::bmPositionComponent;
using biemgine::bmTextureComponent;
using biemgine::bmPhysicsComponent;
using biemgine::bmColorComponent;
using biemgine::bmGroundComponent;

#pragma once

#include "../components/bmGravityComponent.h"

using biemgine::bmColor;

namespace spacebiem
{
    class bmPlanetMoonEntity :
        public bmEntity
    {
    public:
        bmPlanetMoonEntity(float x, float y, bmColor color, float w, float h);
    };
}
