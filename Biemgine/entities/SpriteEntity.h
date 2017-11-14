#pragma once

#include "dlldef.h"
#include "..\components\PositionComponent.h"
#include "..\components\ColorComponent.h"
#include "..\components\TextureComponent.h"
#include "..\primitives\Primitives.h"
#include "Entity.h"

namespace biemgine
{
    class BIEMGINE SpriteEntity :
        public Entity
    {
    public:
        ~SpriteEntity();
        SpriteEntity(std::string texture, float x, float y, Color color, float w, float h, unsigned int layer);
    };
}
