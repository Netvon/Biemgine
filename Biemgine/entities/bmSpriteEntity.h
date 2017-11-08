#pragma once

#include "dlldef.h"
#include "..\components\bmPositionComponent.h"
#include "..\components\bmColorComponent.h"
#include "..\components\bmTextureComponent.h"
#include "..\primitives\bmPrimitives.h"
#include "bmEntity.h"

namespace biemgine {

    class BIEMGINE bmSpriteEntity : public bmEntity
    {
    public:
        ~bmSpriteEntity();
        bmSpriteEntity(std::string texture, float x, float y, bmColor color, float w, float h);
    };
}
