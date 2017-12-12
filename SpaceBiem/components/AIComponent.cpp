#include "AIComponent.h"

namespace spacebiem
{
    AIComponent::AIComponent(bool pCanIdle, bool pCanWander, bool pCanFollow) :
        canIdle(pCanIdle), canWander(pCanWander), canFollow(pCanFollow)
    {}

    void AIComponent::setTarget(Entity * pTarget)
    {
        target = pTarget;
    }

    const Entity & AIComponent::getTarget() const
    {
        return *target;
    }

    bool AIComponent::getCanIdle() const
    {
        return canIdle;
    }

    bool AIComponent::getCanWander() const
    {
        return canWander;
    }

    bool AIComponent::getCanFollow() const
    {
        return canFollow;
    }

    Direction AIComponent::getDirection()
    {
        auto currentTime = time(0);

        if (directionEndTime != 0 && directionEndTime < currentTime) return direction;

        if (direction == Direction::IDLE) {
            if (getCanWander() || getCanFollow()) {
                RandomGenerator & generator = RandomGenerator::getInstance();

                direction = generator.generate(0.f, 1.f) > 0.5 ? Direction::LEFT : Direction::RIGHT;
            }

            directionEndTime = time(0) + 3;
        }
        else {
            direction = Direction::IDLE;
            directionEndTime = time(0) + 1;
        }

        return direction;
    }

    void AIComponent::setDirection(Direction pDirection)
    {
        direction = pDirection;
    }

    bool AIComponent::isDirection(Direction pDirection)
    {
        return getDirection() == pDirection;
    }

    int AIComponent::getDirectionEndTime() const
    {
        return directionEndTime;
    }

    float AIComponent::getForce() const
    {
        return force;
    }
}
