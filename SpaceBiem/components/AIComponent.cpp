#include "AIComponent.h"

namespace spacebiem
{
    AIComponent::AIComponent()
    {
        setState(AIState::IDLE);
    }

    bool AIComponent::isState(AIState pState) const
    {
        return state == pState;
    }

    void AIComponent::setTarget(Entity * pTarget)
    {
        target = pTarget;
    }

    const Entity & AIComponent::getTarget() const
    {
        return *target;
    }

    AIComponent * AIComponent::setState(AIState pState)
    {
        state = pState;

        return this;
    }

    Direction AIComponent::getDirection() const
    {
        return direction;
    }

    void AIComponent::setDirection(Direction pDirection)
    {
        direction = pDirection;
    }

    bool AIComponent::isDirection(Direction pDirection) const
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
