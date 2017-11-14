#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using biemgine::Entity;
using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::UIComponent;
using biemgine::RectangleComponent;

#include "../components/OxygenComponent.h"

namespace spacebiem
{
    class OxygenUIEntity :
        public Entity
    {
    public:
        OxygenUIEntity()
        {
            addComponent("position", new PositionComponent(42, 220));
            addComponent("color", new ColorComponent(255, 255, 255));
            addComponent("ui", new UIComponent);
            addComponent("oxygen", new OxygenComponent);
            addComponent("texture", new TextureComponent("textures/oxygen-hud.png", -17, 0, 255, 40, 2u));
            addComponent("rectangle", new RectangleComponent(204, 36, { 93, 206, 109, 255 }));
        };
    };
}
