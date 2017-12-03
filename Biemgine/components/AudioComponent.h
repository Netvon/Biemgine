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
        AudioComponent(std::string path, int loops = 0, int channel = -1, int volume = 128, int fadeInTime = 1000);
        ~AudioComponent();

        const std::string getPath() const { return path; }
        const int getLoops() const { return loops; }
        const int getChannel() const { return channel; }
        const int getVolume() const { return volume; }
        const int getFadeInTime() const { return fadeInTime; }

    private:
        std::string path;
        int loops;
        int channel;
        int volume;
        int fadeInTime;
    };
}
