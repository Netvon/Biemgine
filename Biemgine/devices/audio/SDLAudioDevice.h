#pragma once

#include "AudioDevice.h"
#include <map>
#include <SDL_mixer.h>
#include <iostream>

using std::string;

namespace biemgine
{
    class SDLAudioDevice :
        public AudioDevice
    {
    public:
        SDLAudioDevice();
        ~SDLAudioDevice();

        void playSoundEffect(std::string path, int loops = 0, int channel = 0);
        void playMusic(std::string path, int loops = -1);

        void PauzeMusic();
        void ResumeMusic();

    private:
        std::map<std::string, Mix_Chunk*> soundEffects;
        std::map<std::string, Mix_Music*> music;

        Mix_Chunk* getSoundEffects(std::string path);
        Mix_Music* getMusic(std::string path);
    };
}
