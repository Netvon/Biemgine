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
        if (directionEndTime != 0 && directionEndTime < time(0)) return direction;

        if (direction != Direction::IDLE) {
            direction = Direction::IDLE;
            directionEndTime = time(0) + 2;
        }

        return direction;
    }

    void AIComponent::setDirection(Direction pDirection)
    {
        direction = pDirection;
    }

    bool AIComponent::isDirection(Direction pDirection)
    {
        return direction == pDirection;
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
