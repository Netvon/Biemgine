#include "AdEntity.h"

namespace spacebiem
{
    AdEntity::AdEntity()
    {
        addComponent("position", new PositionComponent(0, 0));
        addComponent("color", new ColorComponent(Color{0,0,0}));
        
        addComponent("text", new TextComponent(Fonts::Roboto(), "X", Color{ 0, 0, 0 }, true, 25, 25, 1100u, true));
        addComponent("texture", new TextureComponent(Ads::random(), 0, 0, 402, 169, 1000u, true, "", Color::White()));
        addComponent("animation", new AnimationComponent(-169, 25, 500, nullptr, nullptr));
        auto animation = getComponent<AnimationComponent>("animation");

        addComponent("ui", new UIComponent(Size{ 50, 50 }, nullptr, nullptr));
    }
}

