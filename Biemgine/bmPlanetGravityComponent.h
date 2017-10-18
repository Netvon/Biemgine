#pragma once

#include "bmComponent.h"
#include "bmTextureComponent.h"

class bmPlanetGravityComponent :
    public bmComponent
{
public:
    bmPlanetGravityComponent(bmTextureComponent pTextureComponent) : textureComponent(pTextureComponent) {};

    bmTextureComponent& getTextureComponent() {
        return textureComponent;
    };


private:
    bmTextureComponent textureComponent;
};

