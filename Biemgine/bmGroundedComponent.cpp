#include "stdafx.h"
#include "bmGroundedComponent.h"

bool bmGroundedComponent::isGrounded() const
{
    return this->grounded;
}

bmGroundedComponent* bmGroundedComponent::setGrounded(bool grounded)
{
    this->grounded = grounded;

    return this;
}
