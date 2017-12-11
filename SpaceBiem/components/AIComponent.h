#pragma once

#include "stdafx.h"
#include "Biemgine.h"

using biemgine::Component;
using biemgine::PositionComponent;
using biemgine::RandomGenerator;
using biemgine::Entity;

namespace spacebiem
{
    enum class AIState
    {
        IDLE,
        WANDERING,
        FOLLOW
    };

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
        AIComponent::AIComponent();

        bool isState(AIState pState) const;
        AIComponent* setState(AIState pState);

        Direction getDirection() const;
        void setDirection(Direction pDirection);
        bool isDirection(Direction pDirection) const;

        int getDirectionEndTime() const;

        float getForce() const;

        void setTarget(Entity * pTarget);
        const Entity & getTarget() const;

    private:
        AIState state;
        Direction direction = Direction::IDLE;
        int directionEndTime = 0;

        float force = 1.f;

        Entity * target = nullptr;
    };
}
