#pragma once

#include "dlldef.h"
#include "..\primitives\bmPrimitives.h"

namespace biemgine
{
    class BIEMGINE InputManager
    {
    public:
        InputManager();

        void update();
        bool isKeyDown(const char* key) const;
        bmVector getMouseLocation() const;
        bool isLeftMouseDown() const;
        bool isRightMouseDown() const;
        bool isMiddleMouseDown() const;
    private:
        const unsigned char* keyStates;
    };
}
