#include "AdEntity.h"

namespace spacebiem
{
    AdEntity::AdEntity()
    {
        addComponent("position", new PositionComponent(1493, -191));
        addComponent("text", new TextComponent(Fonts::Roboto(), "X", Color{ 0, 0, 0 }, true, 20, 169, 1100u, true));
        addComponent("texture", new TextureComponent(Ads::instance().random(), 4, 50, 382, 134, 1000u, true, "", Color::White()));
        addComponent("texture", new TextureComponent("textures/billboard.png", 0, 0, 391, 191, 1001u, true, "", Color::White()));
       
        auto position = getComponent<PositionComponent>("position");
        addComponent("animation", new AnimationComponent(-191, 0, 500, [position](float newValue) { position->setY(newValue); }, nullptr, true));

        auto animation = getComponent<AnimationComponent>("animation");
        addComponent("ui", new UIComponent(SizeRect{Point{0,159,0}, Size{20, 20}}, [animation](StateManager* e){ animation->playReversed(); }, nullptr));
    }
}

