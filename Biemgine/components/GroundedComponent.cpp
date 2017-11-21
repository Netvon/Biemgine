#include "stdafx.h"
#include "GroundedComponent.h"

namespace biemgine
{
    bool GroundedComponent::isGrounded() const
    {
        return grounded;
    }

    GroundedComponent * GroundedComponent::setGrounded(bool pGrounded, Entity * pGroundedOn)
    {
        grounded = pGrounded;

        if (pGrounded)
            groundedOn = pGroundedOn;

        return this;
    }

    Entity * GroundedComponent::getGroundedOn() const
    {
        return groundedOn;
    }
}
