#include "bmAffectedByGravityComponent.h"

namespace biemgine {
    bmAffectedByGravityComponent::bmAffectedByGravityComponent(bool isAffected) : isAffected(isAffected) {}
    bmAffectedByGravityComponent::~bmAffectedByGravityComponent() {}

    bool bmAffectedByGravityComponent::getIsAffected() const {
        return isAffected;
    }

    float bmAffectedByGravityComponent::getFallingTowardsX() const {
        return fallingTowardsX;
    }

    float bmAffectedByGravityComponent::getFallingTowardsY() const {
        return fallingTowardsY;
    }

    void bmAffectedByGravityComponent::setFallingTowardsX(float value) {
        fallingTowardsX = value;
    }

    void bmAffectedByGravityComponent::setFallingTowardsY(float value) {
        fallingTowardsY = value;
    }
}
