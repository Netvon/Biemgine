#include "stdafx.h"
#include "bmGroundedComponent.h"

namespace biemgine
{
    bool bmGroundedComponent::isGrounded() const
    {
        return grounded;
    }

    bmGroundedComponent* bmGroundedComponent::setGrounded(bool pGrounded)
    {
        grounded = pGrounded;

        return this;
    }
}
