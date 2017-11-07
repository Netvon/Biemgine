#include "stdafx.h"
#include "bmInputManager.h"

namespace biemgine {

    bmInputManager::bmInputManager()
    {
        update();
    }

    void bmInputManager::update()
    {
        SDL_PumpEvents();
        keyStates = SDL_GetKeyboardState(nullptr);
    }

    bool bmInputManager::isKeyDown(const char * key)
    {
        return keyStates[SDL_GetScancodeFromName(key)];
    }

    bool bmInputManager::isKeyDown(const SDL_Scancode key)
    {
        return keyStates[key];
    }
}
