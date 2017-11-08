#pragma once

#include "dlldef.h"
#include "bmComponent.h"

namespace biemgine
{
    class BIEMGINE bmAffectedByGravityComponent
        : public bmComponent
    {
    public:
        bmAffectedByGravityComponent(bool isAffected);
        ~bmAffectedByGravityComponent();

        bool getIsAffected() const;
        float getFallingTowardsX() const;
        float getFallingTowardsY() const;
        void setFallingTowardsX(float value);
        void setFallingTowardsY(float value);

    private:
        bool isAffected;

        float fallingTowardsX, fallingTowardsY = 0.0f;
    };
}
