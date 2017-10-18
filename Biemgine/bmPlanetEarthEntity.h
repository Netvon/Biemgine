#pragma once
#include "stdafx.h"
#include "bmEntity.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"
#include "bmPhysicsComponent.h"
#include "bmRectangleComponent.h"
#include "bmAtmosphereComponent.h"
#include "bmGravityComponent.h"

class bmPlanetEarthEntity : public bmEntity
{
public:
    bmPlanetEarthEntity(float x, float y, bmColor color, float w, float h) {
        addComponent("position", new bmPositionComponent(x, y, 0.f, 25.f));
        addComponent("texture", new bmTextureComponent("textures/planet.png", 0, 0, w, h, 1u));
        addComponent("texture", new bmTextureComponent("textures/atmosphere_clouds.png", w / -2, h / -2, w * 2, h * 2, 9999u));
        addComponent("texture", new bmTextureComponent("textures/atmosphere.png", w / -2, h / -2, w * 2, h * 2));
        addComponent("texture", new bmTextureComponent("textures/gravityField.png", w / -2, h / -2, w * 2, h * 2));
        addComponent("physics", new bmPhysicsComponent(w  , h, true, CIRCLE));
        addComponent("color", new bmColorComponent(color));
        addComponent("atmosphere", new bmAtmosphereComponent(x+(w/2), y+(h/2), w));
    }
};
