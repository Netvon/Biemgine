#include "stdafx.h"
#include "TextUIEntity.h"

namespace biemgine
{
    TextUIEntity::~TextUIEntity() {}

    TextUIEntity::TextUIEntity(float x, float y, Color color, const std::string& pText)
    {
        addComponent<PositionComponent>("position", x, y);
        addComponent<ColorComponent>("color", color);
        addComponent<UIComponent>("ui");
        addComponent<TextComponent>("text", pText);
    }
}
