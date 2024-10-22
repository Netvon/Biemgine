#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using biemgine::Entity;
using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::UIComponent;
using biemgine::RectangleComponent;
using biemgine::TextureComponent;

#include "../components/OxygenComponent.h"

namespace spacebiem
{
    class OxygenUIEntity :
        public Entity
    {
    public:
        OxygenUIEntity(int x = 42, int y = 220)
        {
            addComponent("position", new PositionComponent(x, y));
            addComponent("ui", new UIComponent);
            addComponent("oxygen", new OxygenComponent);
            addComponent("texture", new TextureComponent("textures/oxygen-hud.png", -17, 0, 255, 40, 200u));
            addComponent("texture", new TextureComponent("textures/rectangle.png", 0, 1, 204, 36, 190u, true, "oxygenbar", { 93, 206, 109, 255 }));
            addComponent("texture", new TextureComponent("textures/rectangle.png", 0, 1, 204, 36, 180u, true, "oxygentankbackground", { 51, 51, 51, 255 }));
            addComponent("texture", new TextureComponent("textures/vignet.png", -x, -y, 1932, 1082, 100u, true, "vignet", {142, 12, 12, 0}, 0.0f));
        };
    };
}
