#pragma once

#include "Biemgine.h"

using biemgine::Component;

namespace spacebiem
{
    class MovementComponent :
        public Component
    {
    public:
        MovementComponent();
        float getJumpForce() const;
        void setJumpForce(float pJumpForce);
    private:
        float jumpForce = 10.f;
    };
}
