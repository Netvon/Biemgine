#include "stdafx.h"
#include "ButtonUIEntity.h"
#include "..\globals\Fonts.h"
#include "..\globals\Functions.h"

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
    ButtonUIEntity::ButtonUIEntity(float x, float y, Color buttonColor, Color textcolor, Size size, const string& pText, const string& texturePath, std::function<void(StateManager*)> onClick, std::function<void(StateManager*)> onEnter, string tag)
    {
        std::function<bool()> ifEnabled = [this]() {
            auto ui = getComponent<UIComponent>("ui");
            if (ui == nullptr)
                return false;

            return ui->isEnabled();
        };

        auto click = Functions::combine<StateManager*>(
            Functions::do_if(ifEnabled, Functions::buttonClickSound()),
            onClick
        );

        auto hover = Functions::combine<StateManager*>(
            Functions::do_if(ifEnabled, Functions::buttonHoverSound()),
            onEnter
        );

        addComponent("position", new PositionComponent(x, y));
        addComponent("texture", new TextureComponent(texturePath, 0.f, 0.f, size.width, size.height, 1000u, true, "", buttonColor));
        //addComponent("color", new ColorComponent(buttonColor));
        addComponent("ui", new UIComponent(size, click, hover,(onClick != nullptr)));
        addComponent("text", new TextComponent(Fonts::Roboto(), pText, textcolor, size.width/2, size.height/2, true, true));

        addComponent<ScriptComponent>("script",
            [this](float deltaTime)
        {
            auto ui = getComponent<UIComponent>("ui");
            auto texture = getComponent<TextureComponent>("texture");

            if (!ui->isEnabled()) {
                texture->setColor(texture->getColor().WithAlpha(108));
            }
            else if (!ui->getIsMouseOver()) {
                texture->setColor(texture->getColor().WithAlpha(200));

            }
            else {
                texture->setColor(texture->getColor().WithAlpha(255));
            }
        });

        setTag(tag);
    }
}
