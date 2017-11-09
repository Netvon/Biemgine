#include "stdafx.h"
#include "GroundedComponent.h"

namespace biemgine
{
    GroundedComponent::GroundedComponent(bool grounded)
        : grounded(grounded)
    { }

    GroundedComponent::~GroundedComponent() {}

    bool GroundedComponent::isGrounded() const
    {
        return grounded;
    }

    GroundedComponent* GroundedComponent::setGrounded(bool pGrounded)
    {
        grounded = pGrounded;

        return this;
    }
}
