#pragma once

#include "dlldef.h"

#include "Component.h"
#include "PositionComponent.h"

namespace biemgine
{
    class BIEMGINE TransformComponent :
        public Component
    {
        TransformComponent(float x, float y, float rotation = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f);
        ~TransformComponent();

        float getRotation() const;
        const PositionComponent& getPosition();
        float getScaleX() const;
        float getScaleY() const;

    private:
        float rotation;
        PositionComponent position;
        Vector scale;
    };
}
