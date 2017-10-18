#pragma once
#include "bmPlanetComponentType.h"
#include "bmComponent.h"

class bmPlanettypeComponent :
    public bmComponent
{
public:
    bmPlanettypeComponent(bmPlanetComponentType pType) : type(pType) {};

    bmPlanetComponentType getType() const {
        return type;
    }

private:
    bmPlanetComponentType type;
};
