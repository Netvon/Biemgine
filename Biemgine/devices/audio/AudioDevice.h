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
        virtual void playSoundEffect() = 0;
        virtual void playMusic() = 0;

        virtual void clear() const = 0;
        virtual void present() = 0;
    };
}
