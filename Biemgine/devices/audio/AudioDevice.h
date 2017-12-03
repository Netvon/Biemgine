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

        virtual bool isPlayingMusic(std::string path = "") = 0;
        virtual bool isPlayingSoundEffect(std::string path = "") = 0;

        virtual void playFadeInSoundEffect(std::string path, int loops = 0, int channel = -1, int volume = 128, int fadeInTime = 1000) = 0;
        virtual void playSoundEffect(std::string path, int loops = 0, int channel = -1, int volume = 128) = 0;

        virtual void playFadeInMusic(std::string path, int loops = 0, int fadeInTime = 1000) = 0;
        virtual void playMusic(std::string path, int loops = 0) = 0;
    };
}
