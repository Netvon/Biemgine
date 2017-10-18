#pragma once

#include "bmComponent.h"
#include "bmTextureComponent.h"

class bmPlanetAtmosphereComponent :
    public bmComponent
{
public:
    bmPlanetAtmosphereComponent(bmTextureComponent pTextureComponent) : textureComponent(pTextureComponent){};

    bmTextureComponent& getTextureComponent() {
        return textureComponent;
    };

 
private:
    bmTextureComponent textureComponent;
};

