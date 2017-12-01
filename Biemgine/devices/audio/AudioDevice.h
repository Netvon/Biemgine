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

        virtual bool isPlayingMusic() = 0;

        virtual void playFadeInSoundEffect(std::string path, int loops, int channel, int volume, int fadeInTime) = 0;
        virtual void playSoundEffect(std::string path, int loops, int channel, int volume) = 0;

        virtual void playFadeInMusic(std::string path, int loops, int fadeInTime) = 0;
        virtual void playMusic(std::string path, int loops) = 0;
    };
}
