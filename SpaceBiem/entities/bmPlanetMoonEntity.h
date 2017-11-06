#pragma once
#include "stdafx.h"
#include "bmEntity.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"
#include "bmPhysicsComponent.h"
#include "bmRectangleComponent.h"
#include "bmGroundComponent.h"
#include "bmGravityComponent.h"


class bmPlanetMoonEntity : public bmEntity
{
public:
    bmPlanetMoonEntity(float x, float y, bmColor color, float w, float h) {
        addComponent("position", new bmPositionComponent(x, y));
        addComponent("texture", new bmTextureComponent("textures/moon-plain.png", 0, 0, w, h, 2u));
        addComponent("texture", new bmTextureComponent("textures/moon-TypeA.png", 0 - ((w*1.19f / 2) - w / 2), 0 - ((h*1.19f / 2) - h / 2), w*1.19f, h*1.19f, 1u));
        addComponent("texture", new bmTextureComponent("textures/gravityField.png", w / -2, h / -2, w * 2, h * 2));
        addComponent("physics", new bmPhysicsComponent(w, h, true, CIRCLE));
        addComponent("color", new bmColorComponent(color));
        addComponent("ground", new bmGroundComponent());
        addComponent("gravity", new bmGravityComponent(w / -2, h / -2, w * 2, h * 2, w));
    }
};

