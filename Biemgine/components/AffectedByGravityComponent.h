#pragma once

#include "dlldef.h"
#include "Component.h"
#include "..\primitives\Primitives.h"

namespace biemgine
{
    class BIEMGINE AffectedByGravityComponent
        : public Component
    {
    public:
        AffectedByGravityComponent(bool isAffected);
        ~AffectedByGravityComponent();

        bool getIsAffected() const;
        float getFallingTowardsX() const;
        float getFallingTowardsY() const;
        void setFallingTowardsX(float value);
        void setFallingTowardsY(float value);
        Vector getFallingTowards();

    private:
        bool isAffected;

        float fallingTowardsX, fallingTowardsY = 0.0f;
    };
}
