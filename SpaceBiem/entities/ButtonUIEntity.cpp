#include "stdafx.h"
#include "ButtonUIEntity.h"

using std::string;
using biemgine::PositionComponent;
using biemgine::TextureComponent;
using biemgine::ColorComponent;
using biemgine::UIComponent;
using biemgine::TextComponent;
using biemgine::Size;

namespace spacebiem
{
    ButtonUIEntity::ButtonUIEntity(float x, float y, Color color, float w, float h, const string& pText, std::function<void(StateManager*)> onClick)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("texture", new TextureComponent("textures/button.png", 0.f, 0.f, w, h, 0u));
        addComponent("color", new ColorComponent(185, 238, 253));
        addComponent("ui", new UIComponent({ static_cast<int>(w), static_cast<int>(h) }, onClick));
        addComponent("text", new TextComponent(pText, color));
    }
}
