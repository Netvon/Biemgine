#pragma once

#include "dlldef.h"
#include "bmComponent.h"
#include "PhysicsComponentShape.h"
#include <vector>
#include <map>
#include <string>

#include "..\primitives\bmPrimitives.h"

using namespace std;

namespace biemgine
{
    class BIEMGINE bmTimedForce
    {
    private:
        bmVector force;
        bool isImpulse;
        float ticksLeft;

    public:
        bmTimedForce(float px, float py, float pticksLeft, bool pisImpulse = false);
        ~bmTimedForce();

        bmVector getForce() const;
        float getTicksLeft() const;
        bool getIsImpulse() const;

        bool decreaseTicks();
    };

    class BIEMGINE bmPhysicsComponent :
        public bmComponent
    {
    public:
        bmPhysicsComponent(float colliderW, float colliderH, bool isStatic, PhysicsComponentShape shape, float mass = 22.0f);
        ~bmPhysicsComponent();

        const float& getColliderW() const;
        const float& getColliderH() const;

        PhysicsComponentShape getShape() const;

        bool getIsStatic() const;
        float getForceX() const;
        float getForceY() const;

        float getMass() const;
        float getImpulseX() const;
        float getImpulseY() const;

        void addForce(const string id, float x, float y);

        void addImpulse(const string id, float x, float y);

        void addTimedForce(const string id, float forceX, float forceY, size_t doForTicks, bool isImpulse = false);

        void decreaseTimedForces();

    private:
        bmVector colliderSize;

        map<string, bmTimedForce> timedForces;

        int impulseTicks = 30;

        float mass = 1.0f;
        PhysicsComponentShape shape;
        bool isStatic;

        bool hasTimedForce(const string id) const;
    };
}
