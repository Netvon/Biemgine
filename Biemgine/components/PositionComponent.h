#pragma once

#include "dlldef.h"
#include "Component.h"
#include "..\primitives\Primitives.h"

namespace biemgine
{
    class BIEMGINE PositionComponent :
        public Component
    {
    public:
        PositionComponent(float x = 0, float y = 0, float z = 0, float rotation = 0.0f);
        ~PositionComponent();

        float getOriginX() const;
        float getOriginY() const;
        float getX() const;
        float getY() const;
        float getZ() const;
        float getRotation() const;

        void setX(float x);
        void setY(float y);
        void setOffsetX(float x);
        void setOffsetY(float y);
        void setRotation(float newRotation);

        void add(float x, float y, float z = 0);

    private:
        Vector location;
        Vector offsetLocation;
        float rotation;
    };
}
