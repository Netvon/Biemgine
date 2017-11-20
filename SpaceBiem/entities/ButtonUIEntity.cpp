#include "stdafx.h"
#include "ButtonUIEntity.h"

using std::string;
using biemgine::PositionComponent;
using biemgine::TextureComponent;
using biemgine::ColorComponent;
using biemgine::UIComponent;
using biemgine::TextComponent;
using biemgine::Size;
using biemgine::ScriptComponent;

namespace spacebiem
{
    ButtonUIEntity::ButtonUIEntity(float x, float y, Color buttonColor, Color textcolor, Size size, const string& pText, const string& texturePath, std::function<void(StateManager*)> onClick)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("texture", new TextureComponent(texturePath, 0.f, 0.f, size.width, size.height, 0u, true, "", buttonColor));
        //addComponent("color", new ColorComponent(buttonColor));
        addComponent("ui", new UIComponent(size, onClick));
        addComponent("text", new TextComponent(pText, textcolor, size.width/2, size.height/2, true, true));

        addComponent<ScriptComponent>("script",
            [this]()
        {
            auto ui = getComponent<UIComponent*>("ui");
            auto texture = getComponent<TextureComponent*>("texture");

            if (!ui->getIsMouseOver()) {
                texture->setColor(texture->getColor().WithAlpha(128));
            }
            else {
                texture->setColor(texture->getColor().WithAlpha(255));
            }
        });
    }
}
