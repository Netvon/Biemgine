#include "SDLAudioDevice.h"

namespace biemgine
{
    SDLAudioDevice::SDLAudioDevice()
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
        {
            std::cout << "Mixer initialization error: " << Mix_GetError() << std::endl;
        }
    }

    SDLAudioDevice::~SDLAudioDevice()
    {
        Mix_CloseAudio();
    }

    void SDLAudioDevice::playSoundEffect(std::string path, int loops, int channel)
    {
        if (Mix_PlayChannel(channel, getSoundEffects(path), loops) < 0)
        {
            std::cout << "Play sound effect error: " << Mix_GetError() << std::endl;
        }
    }

    void SDLAudioDevice::playMusic(std::string path, int loops)
    {
        if (Mix_PlayMusic(getMusic(path), loops) < 0)
        {
            std::cout << "Play music error: " << Mix_GetError() << std::endl;
        }
    }

    void SDLAudioDevice::PauzeMusic()
    {
        if (Mix_PlayingMusic() != 0)
        {
            Mix_PauseMusic();
        }
    }

    void SDLAudioDevice::ResumeMusic()
    {
        if (Mix_PausedMusic() != 0)
        {
            Mix_ResumeMusic();
        }
    }

    Mix_Chunk* SDLAudioDevice::getSoundEffects(std::string path)
    {
        if (soundEffects[path] == nullptr) {
            soundEffects[path] = Mix_LoadWAV(path.c_str());
            if (soundEffects[path] == nullptr)
            {
                std::cout << "Sound effect loading error: " << path.c_str() << ". Error: " << Mix_GetError() << std::endl;
            }
        }

        return soundEffects[path];
    }

    Mix_Music* SDLAudioDevice::getMusic(std::string path)
    {
        if (music[path] == nullptr) {
            music[path] = Mix_LoadMUS(path.c_str());
            if (music[path] == nullptr)
            {
                std::cout << "Music loading error: " << path.c_str() << ". Error: " << Mix_GetError() << std::endl;
            }
        }

        return music[path];
    }
}

