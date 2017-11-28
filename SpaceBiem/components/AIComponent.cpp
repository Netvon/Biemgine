#include "AIComponent.h"

namespace spacebiem
{
    AIComponent::AIComponent()
    {
        setState(AIState::IDLE);
    }

    bool AIComponent::isState(AIState pState)
    {
        return state == pState;
    }

    AIComponent * AIComponent::setState(AIState pState)
    {
        state = pState;

        return this;
    }

    Direction AIComponent::getDirection()
    {
        int currentTime = static_cast<int>(time(0));

        if (currentTime > directionEndTime) {
            if (direction == Direction::IDLE) {
                RandomGenerator & generator = RandomGenerator::getInstance();
                direction = generator.generate(0.f, 1.f) > 0.5 ? Direction::LEFT : Direction::RIGHT;
                directionEndTime = currentTime + 10;

                force = generator.generate(0.2f, 0.5f);
            }
            else {
                direction = Direction::IDLE;
                directionEndTime = currentTime + 1;
            }
        }

        return direction;
    }

    bool AIComponent::isDirection(Direction pDirection)
    {
        return getDirection() == pDirection;
    }

    float AIComponent::getForce() const
    {
        return force;
    }
}
