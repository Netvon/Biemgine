#include "stdafx.h"
#include "InputManager.h"

#include <SDL.h>

namespace biemgine
{
    InputManager::InputManager()
    {
        update();
    }

    void InputManager::update()
    {
        SDL_PumpEvents();
        keyStates = SDL_GetKeyboardState(nullptr);
    }

    bool InputManager::isKeyDown(const char * key) const
    {
        return keyStates[SDL_GetScancodeFromName(key)];
    }
}
