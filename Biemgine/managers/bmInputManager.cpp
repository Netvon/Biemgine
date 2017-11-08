#include "stdafx.h"
#include "bmInputManager.h"

#include <SDL.h>

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

    bool bmInputManager::isKeyDown(const char * key) const
    {
        return keyStates[SDL_GetScancodeFromName(key)];
    }
}
