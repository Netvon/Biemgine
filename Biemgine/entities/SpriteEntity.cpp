#include "stdafx.h"
#include "SpriteEntity.h"

namespace biemgine
{
    SpriteEntity::~SpriteEntity() {}

    SpriteEntity::SpriteEntity(std::string texture, float x, float y, Color color, float w, float h, unsigned int layer)
    {
        addComponent<PositionComponent>("position", x, y);
        addComponent<TextureComponent>("texture", texture, 0.0f, 0.0f, static_cast<int>(w), static_cast<int>(h), layer);
        addComponent<ColorComponent>("color", color);
        addComponent<UIComponent>("ui");
    }
}
