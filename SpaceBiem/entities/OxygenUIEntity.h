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
            addComponent("position", new PositionComponent(0, 0));
            addComponent("color", new ColorComponent(185, 238, 253));
            addComponent("ui", new UIComponent);
            addComponent("oxygen", new OxygenComponent);
            addComponent("rectangle", new RectangleComponent(0, 10, { 185, 238, 253, 255 }));
        };
    };
}
