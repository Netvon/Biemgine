#pragma once
#include "bmEntity.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"
#include "bmUIComponent.h"
#include "bmOxygenComponent.h"


class bmOxygenUIEntity : public bmEntity
{
public:
    bmOxygenUIEntity()
    {
        addComponent("position", new bmPositionComponent(0, 0));
        addComponent("color", new bmColorComponent(185, 238, 253));
        addComponent("ui", new bmUIComponent());
        addComponent("oxygen", new bmOxygenComponent());
        addComponent("rectangle", new bmRectangleComponent(0, 10, { 185, 238, 253, 255 }));
    };
};

