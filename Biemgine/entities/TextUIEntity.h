#pragma once

#include "dlldef.h"
#include "..\components\PositionComponent.h"
#include "..\components\ColorComponent.h"
#include "..\components\UIComponent.h"
#include "..\components\TextComponent.h"
#include "..\primitives\Primitives.h"
#include "Entity.h"

namespace biemgine
{
    class BIEMGINE TextUIEntity :
        public Entity
    {
    public:
        TextUIEntity(float x, float y, Color color, std::string pText);
        ~TextUIEntity();
    };
}
