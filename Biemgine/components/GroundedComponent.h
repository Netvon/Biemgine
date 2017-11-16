#pragma once

#include "dlldef.h"
#include "..\entities\Entity.h"
#include "Component.h"

namespace biemgine
{
    class BIEMGINE GroundedComponent :
        public Component
    {
    public:
        bool isGrounded() const;
        GroundedComponent * GroundedComponent::setGrounded(bool pGrounded, Entity * pGroundedOn);
        Entity * getGroundedOn() const;

    private:
        bool grounded = false;
        Entity * groundedOn;
    };
}
