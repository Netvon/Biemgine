#pragma once

#include "bmComponent.h"

class bmGroundedComponent :
    public bmComponent
{
public:
    bmGroundedComponent(bool grounded = false)
        : grounded(grounded)
    { };

    bool isGrounded() const;
    bmGroundedComponent* bmGroundedComponent::setGrounded(bool grounded = false);

private:
    bool grounded = false;
};
