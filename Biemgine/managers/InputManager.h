#pragma once

#include "dlldef.h"
#include "..\primitives\Primitives.h"

namespace biemgine
{
    class BIEMGINE InputManager
    {
    public:
        InputManager();

        void update();
        bool isKeyDown(const char* key) const;
        Point getMouseLocation() const;
        bool isLeftMouseDown() const;
        bool isRightMouseDown() const;
        bool isMiddleMouseDown() const;
    private:
        const unsigned char* keyStates;
    };
}
