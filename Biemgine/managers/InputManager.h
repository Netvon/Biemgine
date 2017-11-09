#pragma once

#include "dlldef.h"

namespace biemgine
{
    class BIEMGINE InputManager
    {
    public:
        InputManager();

        void update();
        bool isKeyDown(const char* key) const;
    private:
        const unsigned char* keyStates;
    };
}
