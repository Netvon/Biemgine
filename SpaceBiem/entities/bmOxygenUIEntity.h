#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using namespace biemgine;

#include "../components/bmOxygenComponent.h"

class bmOxygenUIEntity : public bmEntity
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

