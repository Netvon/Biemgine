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

        bool isPlayingMusic();

        void playFadeInSoundEffect(std::string path, int loops = 0, int channel = -1, int volume = 128, int fadeInTime = 1000);
        void playSoundEffect(std::string path, int loops = 0, int channel = -1, int volume = 128);

        void playFadeInMusic(std::string path, int loops = -1, int fadeInTime = 1000);
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
