#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using biemgine::bmEntity;
using biemgine::bmPositionComponent;
using biemgine::bmColorComponent;
using biemgine::bmUIComponent;
using biemgine::bmRectangleComponent;

#include "../components/bmOxygenComponent.h"

namespace spacebiem
{
    class bmOxygenUIEntity :
        public bmEntity
    {
    public:
        bmOxygenUIEntity()
        {
            addComponent("position", new bmPositionComponent(0, 0));
            addComponent("color", new bmColorComponent(185, 238, 253));
            addComponent("ui", new bmUIComponent);
            addComponent("oxygen", new bmOxygenComponent);
            addComponent("rectangle", new bmRectangleComponent(0, 10, { 185, 238, 253, 255 }));
        };
    };
}
