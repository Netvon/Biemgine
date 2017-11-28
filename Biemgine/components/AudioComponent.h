#pragma once

#include "Component.h"
#include "dlldef.h"
#include <string>

namespace biemgine
{
    class BIEMGINE AudioComponent :
        public Component
    {
    public:
        AudioComponent(std::string pPath, int pChannel = -1, int pLoops = 0);
        ~AudioComponent();

    private:
        std::string path;
        int channel;
        int loops;
    };
}
