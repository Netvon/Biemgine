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

    float AffectedByGravityComponent::getMass() const {
        return mass;
    }

    void AffectedByGravityComponent::setMass(float pMass) {
        mass = pMass;
    }

    float AffectedByGravityComponent::getRadius() const {
        return radius;
    }

    void AffectedByGravityComponent::setRadius(float pRadius) {
        radius = pRadius;
    }

    float AffectedByGravityComponent::getEscapeVelocity() const {
        return 0.0f;
    }
}
