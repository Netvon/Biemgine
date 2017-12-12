#pragma once

#include <vector>
#include <map>
#include <SDL_mixer.h>
#include <iostream>
#include "AudioDevice.h"

namespace biemgine
{
    class SDLAudioDevice :
        public AudioDevice
    {
    public:

        SDLAudioDevice();
        ~SDLAudioDevice();

        bool isPlayingMusic(std::string path = "");
        bool isPlayingSoundEffect(std::string path = "");

        void playFadeInSoundEffect(std::string path, int loops = 0, int channel = -1, int volume = 128, int fadeInTime = 1000);
        void playSoundEffect(std::string path, int loops = 0, int channel = -1, int volume = 128);

        void playFadeInMusic(std::string path, int loops = 0, int volume = 128, int fadeInTime = 1000);
        void playMusic(std::string path, int loops = 0, int volume = 128);

        void pauzeMusic();
        void resumeMusic();

        void stopSoundEffect(std::string path);
        void fadeOutSoundEffect(std::string path, int fadeOutTime);

    private:
        std::map<std::string, Mix_Chunk*> soundEffects;
        std::map<std::string, Mix_Music*> music;

        std::string currentlyPlayingMusic;
        std::map<std::string, int> currentlyPlayingSoundEffects;

        Mix_Chunk* getSoundEffects(std::string path);
        Mix_Music* getMusic(std::string path);
    };
}
