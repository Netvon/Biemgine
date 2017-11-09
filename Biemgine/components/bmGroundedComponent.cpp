#include "stdafx.h"
#include "bmGroundedComponent.h"

namespace biemgine
{
    bmGroundedComponent::bmGroundedComponent(bool grounded)
        : grounded(grounded)
    { }

    bmGroundedComponent::~bmGroundedComponent() {}

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
