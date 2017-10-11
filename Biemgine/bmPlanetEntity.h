#pragma once
#include "bmEntity.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"
#include "bmPhysicsComponent.h"
#include "bmRectangleComponent.h"

class bmPlanetEntity : public bmEntity
{
public:
    bmPlanetEntity(float x, float y, bmColor color, float w, float h) {
        addComponent("position", new bmPositionComponent(x, y));
        addComponent("texture", new bmTextureComponent("textures/planet.png", w, h));
        addComponent("physics", new bmPhysicsComponent(w, h, true, CIRCLE));
        addComponent("color", new bmColorComponent(color));
    }
};

