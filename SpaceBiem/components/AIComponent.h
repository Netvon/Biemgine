#pragma once

#include "stdafx.h"
#include "Biemgine.h"

using biemgine::Component;
using biemgine::PositionComponent;
using biemgine::RandomGenerator;
using biemgine::Entity;

namespace spacebiem
{
    enum class Direction
    {
        IDLE,
        LEFT,
        RIGHT
    };

    class AIComponent :
        public Component
    {
    public:
        AIComponent::AIComponent(bool pCanIdle = true, bool pCanWander = true, bool pCanFollow = true);

        Direction getDirection();
        void setDirection(Direction pDirection);
        bool isDirection(Direction pDirection);

        int getDirectionEndTime() const;

        float getForce() const;

        void setTarget(Entity * pTarget);
        const Entity & getTarget() const;

        bool getCanIdle() const;
        bool getCanWander() const;
        bool getCanFollow() const;

    private:
        Direction direction = Direction::LEFT;
        int directionEndTime = 0;

        float force = 1.f;

        Entity * target = nullptr;

        bool canIdle = true;
        bool canWander = true;
        bool canFollow = true;
    };
}
