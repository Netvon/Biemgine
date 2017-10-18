#pragma once
#include "bmEntity.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"
#include "bmPhysicsComponent.h"
#include "bmRectangleComponent.h"
#include "bmPlanettypeComponent.h"
#include "bmPlanetAtmosphereComponent.h"

class bmPlanetEntity : public bmEntity
{
public:
    bmPlanetEntity(float x, float y, bmColor color, float w, float h) {
        addComponent("position", new bmPositionComponent(x, y));
        addComponent("texture", new bmTextureComponent("textures/planet.png", w, h));
        addComponent("physics", new bmPhysicsComponent(w, h, true, CIRCLE));
        addComponent("color", new bmColorComponent(color));
        addComponent("planettype", new bmPlanettypeComponent(EARTH));
        addComponent("atmosphere", new bmPlanetAtmosphereComponent(bmTextureComponent("textures/atmosphere.png", 0, 0,w, h)));
    }
};

