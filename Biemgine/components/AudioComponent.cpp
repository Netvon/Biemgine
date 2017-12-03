#include "AudioComponent.h"

namespace biemgine
{
    AudioComponent::AudioComponent(std::string path, int loops, int channel, int volume, int fadeInTime)
        : path(path), loops(loops), channel(channel), volume(volume), fadeInTime(fadeInTime)
    {
    }

    AudioComponent::~AudioComponent()
    {
    }
}


