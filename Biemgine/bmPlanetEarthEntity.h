#pragma once
#include "stdafx.h"
#include "bmEntity.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"
#include "bmPhysicsComponent.h"
#include "bmRectangleComponent.h"
#include "bmPlanettypeComponent.h"
#include "bmPlanetAtmosphereComponent.h"
#include "bmPlanetGravityComponent.h"

class bmPlanetEarthEntity : public bmEntity
{
public:
    bmPlanetEarthEntity(float x, float y, bmColor color, float w, float h) {
        addComponent("position", new bmPositionComponent(x, y));
        addComponent("texture", new bmTextureComponent("textures/planet.png", 0, 0, w, h, 1u));
        addComponent("texture", new bmTextureComponent("textures/atmosphere_clouds.png", w / -2, h / -2, w * 2, h * 2, 9999u));
        addComponent("texture", new bmTextureComponent("textures/atmosphere.png", w / -2, h / -2, w * 2, h * 2));
        addComponent("texture", new bmTextureComponent("textures/gravityField.png", w / -2, h / -2, w * 2, h * 2));
        addComponent("physics", new bmPhysicsComponent(w  , h, true, CIRCLE));
        addComponent("color", new bmColorComponent(color));
        addComponent("planettype", new bmPlanettypeComponent(EARTH));
        addComponent("atmosphere", new bmPlanetAtmosphereComponent(w / -2, h / -2, w * 2, h * 2));
    }
};
