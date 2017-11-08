#pragma once

#include "dlldef.h"
#include "bmComponent.h"

namespace biemgine
{
    class BIEMGINE bmGroundedComponent :
        public bmComponent
    {
    public:
        bmGroundedComponent(bool grounded = false);
        ~bmGroundedComponent();

        bool isGrounded() const;
        bmGroundedComponent* bmGroundedComponent::setGrounded(bool grounded = false);

    private:
        bool grounded = false;
    };
}
