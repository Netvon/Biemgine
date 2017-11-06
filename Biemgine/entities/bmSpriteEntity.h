#pragma once
#include "bmEntity.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"
#include "bmPhysicsComponent.h"
#include "bmRectangleComponent.h"

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

