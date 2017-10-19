#pragma once
#include "stdafx.h"
#include "bmEntity.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"
#include "bmPhysicsComponent.h"
#include "bmRectangleComponent.h"
#include "bmEntityTypeComponent.h"

class bmPlanetMoonEntity : public bmEntity
{
public:
    bmPlanetMoonEntity(float x, float y, bmColor color, float w, float h) {
        addComponent("position", new bmPositionComponent(x, y));
        addComponent("texture", new bmTextureComponent("textures/moonPlanet.png", w, h));
        addComponent("physics", new bmPhysicsComponent(w, h, true, CIRCLE));
        addComponent("color", new bmColorComponent(color));
        addComponent("entityType", new bmEntityTypeComponent(PLANET_MOON));
    }
};

