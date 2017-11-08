#include "bmPhysicsComponent.h"

namespace biemgine {

    bmTimedForce::bmTimedForce(float px, float py, float pticksLeft, bool pisImpulse) :
        force({ px, py }), ticksLeft(pticksLeft), isImpulse(pisImpulse) {}

    bmTimedForce::~bmTimedForce() {}
    bmVector bmTimedForce::getForce() const { return force; }
    float bmTimedForce::getTicksLeft() const { return ticksLeft; }
    bool bmTimedForce::getIsImpulse() const { return isImpulse; }

    bool bmTimedForce::decreaseTicks() {
        if (ticksLeft - 1 == 0)
            return true;

        ticksLeft--;
        return false;
    }

    bmPhysicsComponent::bmPhysicsComponent(float colliderW, float colliderH, bool isStatic, PhysicsComponentShape shape, float mass)
        : colliderSize({ colliderW, colliderH }), shape(shape), isStatic(isStatic), mass(mass)
    {

    };

    bmPhysicsComponent::~bmPhysicsComponent()
    {
    }

    const float & bmPhysicsComponent::getColliderW() const {
        return colliderSize.x;
    }

    const float & bmPhysicsComponent::getColliderH() const {
        return colliderSize.y;
    }

    PhysicsComponentShape bmPhysicsComponent::getShape() const {
        return shape;
    }

    bool bmPhysicsComponent::getIsStatic() const {
        return isStatic;
    }

    float bmPhysicsComponent::getForceX() const {
        bmVector f = { 0,0 };

        for (auto force : timedForces) {
            if (!force.second.getIsImpulse())
                f += force.second.getForce();
        }

        return f.x;
    }

    float bmPhysicsComponent::getForceY() const {
        bmVector f = { 0,0 };

        for (auto force : timedForces) {
            if (!force.second.getIsImpulse())
                f += force.second.getForce();
        }

        return f.y;
    }

    float bmPhysicsComponent::getMass() const {
        return mass;
    }

    float bmPhysicsComponent::getImpulseX() const {
        bmVector f = { 0,0 };

        for (auto force : timedForces) {
            if (force.second.getIsImpulse())
                f += force.second.getForce();
        }

        return f.x;
    }

    float bmPhysicsComponent::getImpulseY() const {
        bmVector f = { 0,0 };

        for (auto force : timedForces) {
            if (force.second.getIsImpulse())
                f += force.second.getForce();
        }

        return f.y;
    }

    void bmPhysicsComponent::addForce(const string id, float x, float y) {
        addTimedForce(id, x, y, 1);
    }

    void bmPhysicsComponent::addImpulse(const string id, float x, float y) {
        addTimedForce(id, x, y, 1, true);
    }

    void bmPhysicsComponent::addTimedForce(const string id, float forceX, float forceY, size_t doForTicks, bool isImpulse)
    {
        if (hasTimedForce(id))
            return;

        auto inner = bmTimedForce(forceX, forceY, static_cast<float>(doForTicks), isImpulse);

        timedForces.insert(pair<string, bmTimedForce>(id, inner));
    }

    void bmPhysicsComponent::decreaseTimedForces() {
        for (auto it = timedForces.begin(); it != timedForces.end();) {
            bmTimedForce& inner = it->second;

            if (inner.decreaseTicks())
                it = timedForces.erase(it);
            else
                ++it;
        }
    }

    bool bmPhysicsComponent::hasTimedForce(const string id) const {
        return timedForces.find(id) != timedForces.end();
    }
}
