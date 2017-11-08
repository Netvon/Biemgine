#pragma once

#include "dlldef.h"

#include "bmComponent.h"
#include "bmPositionComponent.h"

namespace biemgine
{
    class BIEMGINE bmTransformComponent :
        public bmComponent
    {
        bmTransformComponent(float x, float y, float rotation = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f);
        ~bmTransformComponent();

        float getRotation() const;
        const bmPositionComponent& getPosition();
        float getScaleX() const;
        float getScaleY() const;

    private:
        float rotation;
        bmPositionComponent position;
        bmVector scale;
    };
}
