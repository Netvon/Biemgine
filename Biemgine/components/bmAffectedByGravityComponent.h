#pragma once
#include "bmComponent.h"

namespace biemgine
{
    class bmAffectedByGravityComponent
        : public bmComponent
    {
    public:
        bmAffectedByGravityComponent(bool isAffected) : isAffected(isAffected) {};

        bool getIsAffected() const {
            return isAffected;
        }

        float getFallingTowardsX() const {
            return fallingTowardsX;
        }

        float getFallingTowardsY() const {
            return fallingTowardsY;
        }

        void setFallingTowardsX(float value) {
            fallingTowardsX = value;
        }

        void setFallingTowardsY(float value) {
            fallingTowardsY = value;
        }

    private:
        bool isAffected;

        float fallingTowardsX, fallingTowardsY = 0.0f;
    };
}
