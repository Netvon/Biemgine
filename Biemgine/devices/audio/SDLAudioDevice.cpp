#include "SDLAudioDevice.h"

namespace biemgine
{
    SDLAudioDevice::SDLAudioDevice()
    {
        int flags = MIX_INIT_OGG | MIX_INIT_MP3;
        if (Mix_Init(flags) & flags != flags)
        {
            std::cout << "Mix_Init: Failed to init required ogg and mp3! " << Mix_GetError() << std::endl;
            return;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
        {
            std::cout << "Mixer initialization error: " << Mix_GetError() << std::endl;
            return;
        }

        Mix_AllocateChannels(16);
    }

    SDLAudioDevice::~SDLAudioDevice()
    {
        for (std::pair<std::string, Mix_Chunk*>  mixChunk : soundEffects)
        {
            Mix_FreeChunk(mixChunk.second);
        }

        for (std::pair<std::string, Mix_Music*> mixMusic : music)
        {
            Mix_FreeMusic(mixMusic.second);
        }

        Mix_CloseAudio();
    }

    bool SDLAudioDevice::isPlayingMusic()
    {
        return Mix_PlayingMusic();
    }

    void SDLAudioDevice::playFadeInSoundEffect(std::string path, int loops, int channel, int volume, int fadeInTime)
    {
        int playChannel = Mix_FadeInChannel(channel, getSoundEffects(path), loops, fadeInTime);
        if (playChannel < 0)
        {
            std::cout << "Play sound effect error: " << Mix_GetError() << std::endl;
            return;
        }

        Mix_Volume(playChannel, volume);
    }

    void SDLAudioDevice::playSoundEffect(std::string path, int loops, int channel, int volume)
    {
        int playChannel = Mix_PlayChannel(channel, getSoundEffects(path), loops);
        if (playChannel < 0)
        {
            std::cout << "Play sound effect error: " << Mix_GetError() << std::endl;
            return;
        }

        Mix_Volume(playChannel, volume);
    }

    void SDLAudioDevice::playFadeInMusic(std::string path, int loops, int fadeInTime)
    {
        if (Mix_FadeInMusic(getMusic(path), loops, fadeInTime) < 0)
        {
            std::cout << "Play music error: " << Mix_GetError() << std::endl;
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

