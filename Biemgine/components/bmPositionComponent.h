#pragma once

#include "dlldef.h"
#include "bmComponent.h"
#include "..\primitives\bmPrimitives.h"

namespace biemgine
{
    class BIEMGINE bmPositionComponent :
        public bmComponent
    {
    public:
        bmPositionComponent(float x = 0, float y = 0, float z = 0, float rotation = 0.0f);
        ~bmPositionComponent();

        float getX() const;
        float getY() const;
        float getZ() const;
        float getRotation() const;

        void setX(float x);
        void setY(float y);
        void setRotation(float newRotation);

        void add(float x, float y, float z = 0);

    private:
        bmVector location;
        float rotation;
    };
}
