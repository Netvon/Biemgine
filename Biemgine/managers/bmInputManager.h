#pragma once

#include "dlldef.h"

namespace biemgine {
    class BIEMGINE bmInputManager
    {
    public:
        bmInputManager();

        void update();
        bool isKeyDown(const char* key) const;
    private:
        const unsigned char* keyStates;
    };
}
