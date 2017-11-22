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
        OxygenUIEntity()
        {
            addComponent<PositionComponent>("position", 42, 220);
            addComponent("ui", new UIComponent);
            addComponent("oxygen", new OxygenComponent);
            addComponent<TextureComponent>("texture", "textures/oxygen-hud.png", -17, 0, 255, 40, 200u);
            addComponent<TextureComponent>("texture", "textures/rectangle.png", 0, 1, 204, 36, 190u, true, "oxygenbar", { 93, 206, 109, 255 });
            addComponent<TextureComponent>("texture", "textures/rectangle.png", 0, 1, 204, 36, 180u, true, "oxygentankbackground", { 51, 51, 51, 255 });
        };
    };
}
