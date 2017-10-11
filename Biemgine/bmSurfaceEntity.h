#pragma once
#include "bmEntity.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"
#include "bmPhysicsComponent.h"
#include "bmRectangleComponent.h"

class bmSurfaceEntity : public bmEntity
{
public:
    bmSurfaceEntity(float x, float y, bmColor color, float w, float h) {
        addComponent("position", new bmPositionComponent(x, y));
        addComponent("rectangle", new bmRectangleComponent(w, h, color));
        addComponent("physics", new bmPhysicsComponent(w, h, true, RECTANGLE));
    }
};

