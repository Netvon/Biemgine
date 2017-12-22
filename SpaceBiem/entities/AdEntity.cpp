#include "AdEntity.h"

namespace spacebiem
{
    AdEntity::AdEntity()
    {
        addComponent("position", new PositionComponent(1493, -169));
        addComponent("text", new TextComponent(Fonts::Roboto(), "X", Color{ 0, 0, 0 }, true, 25, 25, 1100u, true));
        addComponent("texture", new TextureComponent(Ads::random(), 0, 0, 402, 169, 1000u, true, "", Color::White()));

        auto position = getComponent<PositionComponent>("position");
        addComponent("animation", new AnimationComponent(-169, 25, 500, [position](float newValue) { position->setY(newValue); }, nullptr, true));

        auto animation = getComponent<AnimationComponent>("animation");
        addComponent("ui", new UIComponent(SizeRect{Point{0,0,0}, Size{50, 50}}, [animation](StateManager* e) { animation->playReversed(); }, nullptr));
    }
}

