#include "AffectedByGravityComponent.h"

namespace biemgine
{
    AffectedByGravityComponent::AffectedByGravityComponent(bool isAffected) : isAffected(isAffected) {}
    AffectedByGravityComponent::~AffectedByGravityComponent() {}

    bool AffectedByGravityComponent::getIsAffected() const {
        return isAffected;
    }

    float AffectedByGravityComponent::getFallingTowardsX() const {
        return fallingTowardsX;
    }

    float AffectedByGravityComponent::getFallingTowardsY() const {
        return fallingTowardsY;
    }

    void AffectedByGravityComponent::setFallingTowardsX(float value) {
        fallingTowardsX = value;
    }

    void AffectedByGravityComponent::setFallingTowardsY(float value) {
        fallingTowardsY = value;
    }

    Vector AffectedByGravityComponent::getFallingTowards()
    {
        return { fallingTowardsX, fallingTowardsY };
    }
}
