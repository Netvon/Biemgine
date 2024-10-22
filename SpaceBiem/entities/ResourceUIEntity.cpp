#include "stdafx.h"
#include "ResourceUIEntity.h"
#include "..\components\ResourceBonusComponent.h"
#include "..\globals\Fonts.h"

using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::TextComponent;
using biemgine::UIComponent;

namespace spacebiem
{
    ResourceUIEntity::ResourceUIEntity(float x, float y, Color color, std::string resourceName, int defaultAmount, int pFontSize, string tag)
    {
        setTag(tag);

        addComponent("position", new PositionComponent(x, y));
        addComponent("color", new ColorComponent(color));
        addComponent("text", new TextComponent(Fonts::Roboto(pFontSize)));
        addComponent("ui", new UIComponent);
        addComponent("resourcebonus", new ResourceBonusComponent(resourceName, defaultAmount));
    }
}
