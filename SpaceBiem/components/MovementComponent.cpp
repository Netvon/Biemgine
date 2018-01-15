#include "MovementComponent.h"

namespace spacebiem
{
    MovementComponent::MovementComponent()
    {}

    float MovementComponent::getJumpForce() const
    {
        return jumpForce;
    }

    void MovementComponent::setJumpForce(float pJumpForce)
    {
        jumpForce = pJumpForce;
    }
}
