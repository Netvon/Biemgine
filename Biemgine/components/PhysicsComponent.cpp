#include "PhysicsComponent.h"

namespace biemgine
{
    TimedForce::TimedForce(float px, float py, float pticksLeft, bool pisImpulse) :
        force({ px, py }), ticksLeft(pticksLeft), isImpulse(pisImpulse) {}

    TimedForce::~TimedForce() {}
    Vector TimedForce::getForce() const { return force; }
    float TimedForce::getTicksLeft() const { return ticksLeft; }
    bool TimedForce::getIsImpulse() const { return isImpulse; }

    bool TimedForce::decreaseTicks() {
        if (ticksLeft - 1 == 0)
            return true;

        ticksLeft--;
        return false;
    }

    PhysicsComponent::PhysicsComponent(float colliderW, float colliderH, bool isStatic, PhysicsComponentShape shape, float mass)
        : colliderSize({ colliderW, colliderH }), shape(shape), isStatic(isStatic), density(mass), initialized(false) {}

    PhysicsComponent::~PhysicsComponent() {}

    const float & PhysicsComponent::getColliderW() const {
        return colliderSize.x;
    }

    const float & PhysicsComponent::getColliderH() const {
        return colliderSize.y;
    }

    PhysicsComponentShape PhysicsComponent::getShape() const {
        return shape;
    }

    bool PhysicsComponent::getIsStatic() const {
        return isStatic;
    }

    float PhysicsComponent::getForceX() const {
        Vector f = { 0,0 };

        for (auto force : timedForces) {
            if (!force.second.getIsImpulse())
                f += force.second.getForce();
        }

        return f.x;
    }

    float PhysicsComponent::getForceY() const {
        Vector f = { 0,0 };

        for (auto force : timedForces) {
            if (!force.second.getIsImpulse())
                f += force.second.getForce();
        }

        return f.y;
    }

    float PhysicsComponent::getDensity() const {
        return density;
    }

    float PhysicsComponent::getMass() const
    {
        return mass;
    }

    void PhysicsComponent::setMass(float pMass)
    {
        mass = pMass;
    }

    float PhysicsComponent::getImpulseX() const {
        Vector f = { 0,0 };

        for (auto force : timedForces) {
            if (force.second.getIsImpulse())
                f += force.second.getForce();
        }

        return f.x;
    }

    float PhysicsComponent::getImpulseY() const {
        Vector f = { 0,0 };

        for (auto force : timedForces) {
            if (force.second.getIsImpulse())
                f += force.second.getForce();
        }

        return f.y;
    }

    float PhysicsComponent::getFriction() const
    {
        return friction;
    }

    void PhysicsComponent::setFriction(float pFriction)
    {
        friction = pFriction;
    }

    Vector PhysicsComponent::getVelocity() const
    {
        return velocity;
    }

    void PhysicsComponent::setVelocity(Vector pVelocity, bool pHasCustomVelocity)
    {
        hasCustomVelocity = pHasCustomVelocity;
        velocity = pVelocity;
    }

    void PhysicsComponent::addForce(const string id, float x, float y) {
        addTimedForce(id, x, y, 1);
    }

    void PhysicsComponent::addImpulse(const string id, float x, float y) {
        addTimedForce(id, x, y, 1, true);
    }

    void PhysicsComponent::addTimedForce(const string id, float forceX, float forceY, size_t doForTicks, bool isImpulse)
    {
        if (hasTimedForce(id))
            return;

        auto inner = TimedForce(forceX, forceY, static_cast<float>(doForTicks), isImpulse);

        timedForces.insert(pair<string, TimedForce>(id, inner));
    }

    void PhysicsComponent::decreaseTimedForces() {
        for (auto it = timedForces.begin(); it != timedForces.end();) {
            TimedForce& inner = it->second;

            if (inner.decreaseTicks())
                it = timedForces.erase(it);
            else
                ++it;
        }
    }

    bool PhysicsComponent::getHasCustomVelocity() const
    {
        return hasCustomVelocity;
    }

    bool PhysicsComponent::hasTimedForce(const string id) const {
        return timedForces.find(id) != timedForces.end();
    }

    float PhysicsComponent::getLinearDamping() const
    {
        return linearDamping;
    }

    void PhysicsComponent::setLinearDamping(float pLinearDampening)
    {
        linearDamping = pLinearDampening;
    }
}
