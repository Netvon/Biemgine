#pragma once

#include "dlldef.h"
#include <string>

using std::string;

namespace biemgine
{
    class BIEMGINE AudioDevice
    {
    public:
        virtual ~AudioDevice() {}
        virtual void playSoundEffect(std::string path, int loops, int channel) = 0;
        virtual void playMusic(std::string path, int loops) = 0;
    };
}
