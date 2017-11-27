#pragma once

#include "AudioDevice.h"
#include <map>
#include <SDL_mixer.h>

using std::string;

namespace biemgine
{
    class SDLAudioDevice :
        public AudioDevice
    {
    public:
        SDLAudioDevice();
        ~SDLAudioDevice();

        void playSoundEffect();
        void playMusic();

        void clear() const;
        void present();

    private:
        std::map<std::string, Mix_Chunk*> chunks;
        std::map<std::string, Mix_Music*> music;
    };
}
