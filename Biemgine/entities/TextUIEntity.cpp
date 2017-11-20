#include "stdafx.h"
#include "TextUIEntity.h"

namespace biemgine
{
    TextUIEntity::~TextUIEntity() {}

    TextUIEntity::TextUIEntity(float x, float y, Color color, const std::string& pText)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("color", new ColorComponent(color));
        addComponent("ui", new UIComponent);
        addComponent("text", new TextComponent(pText));
    }
}
