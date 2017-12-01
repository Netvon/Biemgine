#include "stdafx.h"
#include "SpriteEntity.h"

namespace biemgine
{
    SpriteEntity::~SpriteEntity() {}

    SpriteEntity::SpriteEntity(std::string texture, float x, float y, Color color, float w, float h, unsigned int layer, string tag)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("texture", new TextureComponent(texture, 0, 0, static_cast<int>(w), static_cast<int>(h), layer));
        addComponent("color", new ColorComponent(color));
        addComponent("ui", new UIComponent);

        setTag(tag);
    }
}
