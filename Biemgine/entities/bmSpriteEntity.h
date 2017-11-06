#pragma once

#include "..\components\bmPositionComponent.h"
#include "..\components\bmColorComponent.h"
#include "..\components\bmTextureComponent.h"
#include "..\components\bmPhysicsComponent.h"
#include "..\components\bmRectangleComponent.h"
#include "..\primitives\bmColor.h"
#include "bmEntity.h"

class bmSpriteEntity : public bmEntity
{
public:
    bmSpriteEntity(std::string texture, float x, float y, bmColor color, float w, float h)
    {
        addComponent("position", new bmPositionComponent(x, y));
        addComponent("texture", new bmTextureComponent(texture, 0, 0, w, h));
        addComponent("color", new bmColorComponent(color));
    }
};

