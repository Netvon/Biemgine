#pragma once
#include "bmComponent.h"
#include "PhysicsComponentShape.h"
#include <glm\glm.hpp>
#include <vector>
#include <map>
#include <string>

using namespace std;
using namespace glm;

class bmTimedForce {
private:
    vec2 force;
    bool isImpulse;
    size_t ticksLeft;

public:
    bmTimedForce(float px, float py, size_t pticksLeft, bool pisImpulse = false) :
        force(px, py), ticksLeft(pticksLeft), isImpulse(pisImpulse) {}

    vec2 getForce() const { return force; }
    float getTicksLeft() const { return ticksLeft; }
    bool getIsImpulse() const { return isImpulse; }

    bool decreaseTicks() {
        if (ticksLeft - 1 == 0)
            return true;

        ticksLeft--;
        return false;
    }
};


class bmPhysicsComponent :
    public bmComponent
{
public:
    bmPhysicsComponent(float colliderW, float colliderH, bool isStatic, PhysicsComponentShape shape, float mass = 22.0f)
        : colliderSize(colliderW, colliderH), shape(shape), isStatic(isStatic), mass(mass)
    {
       
    };

    const float& getColliderW() const {
        return colliderSize.x;
    }

    const float& getColliderH() const {
        return colliderSize.y;
    }

    PhysicsComponentShape getShape() const {
        return shape;
    }

    bool getIsStatic() const {
        return isStatic;
    }

    float getForceX() const {
        vec2 f = { 0,0 };

        for (auto force : timedForces) {
            if(!force.second.getIsImpulse())
                f += force.second.getForce();
        }

        return f.x;
    }

    float getForceY() const {
        vec2 f = { 0,0 };

        for (auto force : timedForces) {
            if (!force.second.getIsImpulse())
                f += force.second.getForce();
        }

        return f.y;
    }

    float getMass() const {
        return mass;
    }

    float getImpulseX() const {
        vec2 f = { 0,0 };

        for (auto force : timedForces) {
            if (force.second.getIsImpulse())
                f += force.second.getForce();
        }

        return f.x;
    }

    float getImpulseY() const {
        vec2 f = { 0,0 };

        for (auto force : timedForces) {
            if (force.second.getIsImpulse())
                f += force.second.getForce();
        }

        return f.y;
    }

    void addForce(const string id, float x, float y) {
        addTimedForce(id, x, y, 1);
    }

    void addImpulse(const string id, float x, float y) {
        addTimedForce(id, x, y, 1, true);
    }

    void addTimedForce(const string id, float forceX, float forceY, size_t doForTicks, bool isImpulse = false)
    {
        if (hasTimedForce(id))
            return;

        auto inner = bmTimedForce(forceX, forceY, doForTicks, isImpulse);

        timedForces.insert(pair<string, bmTimedForce>(id, inner));
    }

    void decreaseTimedForces() {
        for (auto it = timedForces.begin(); it != timedForces.end();) {
            bmTimedForce& inner = it->second;

            if (inner.decreaseTicks())
                it = timedForces.erase(it);
            else
                ++it;
        }
    }

private:
    vec2 colliderSize;

    map<string, bmTimedForce> timedForces;

    int impulseTicks = 30;

    float mass = 1.0f;
    PhysicsComponentShape shape;
    bool isStatic;

    bool hasTimedForce(const string id) const {
        return timedForces.find(id) != timedForces.end();
    }
};
