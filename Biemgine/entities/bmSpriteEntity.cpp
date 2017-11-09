#include "stdafx.h"
#include "bmSpriteEntity.h"

namespace biemgine
{
    bmSpriteEntity::~bmSpriteEntity() {}

    bmSpriteEntity::bmSpriteEntity(std::string texture, float x, float y, bmColor color, float w, float h)
    {
        addComponent("position", new bmPositionComponent(x, y));
        addComponent("texture", new bmTextureComponent(texture, 0, 0, w, h));
        addComponent("color", new bmColorComponent(color));
    }
}
