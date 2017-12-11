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

        float getMass() const;
        void setMass(float pMass);
        float getRadius() const;
        void setRadius(float pRadius);
        float getEscapeVelocity() const;

    private:
        bool isAffected;

        float fallingTowardsX, fallingTowardsY = 0.0f;
        float mass;
        float radius;
    };
}
