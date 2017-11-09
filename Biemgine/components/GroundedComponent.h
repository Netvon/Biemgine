#pragma once

#include "dlldef.h"
#include "Component.h"

namespace biemgine
{
    class BIEMGINE GroundedComponent :
        public Component
    {
    public:
        GroundedComponent(bool grounded = false);
        ~GroundedComponent();

        bool isGrounded() const;
        GroundedComponent* GroundedComponent::setGrounded(bool grounded = false);

    private:
        bool grounded = false;
    };
}
