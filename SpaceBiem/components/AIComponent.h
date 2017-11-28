#pragma once

#include "stdafx.h"
#include "Biemgine.h"

using biemgine::Component;
using biemgine::RandomGenerator;

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

        bool isState(AIState pState);
        AIComponent* setState(AIState pState);

        Direction getDirection();
        bool isDirection(Direction pDirection);

        float getForce() const;

    private:
        AIState state;
        Direction direction = Direction::IDLE;
        int directionEndTime = 0;

        float force = 1.f;
    };
}
