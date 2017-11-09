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

    bmVector bmInputManager::getMouseLocation() const
    {
        int x = 0, y = 0;

        SDL_GetMouseState(&x, &y);

        return { static_cast<float>(x), static_cast<float>(y) };
    }

    bool bmInputManager::isLeftMouseDown() const
    {
        return SDL_BUTTON(SDL_BUTTON_LEFT);
    }

    bool bmInputManager::isRightMouseDown() const
    {
        return SDL_BUTTON(SDL_BUTTON_RIGHT);
    }

    bool bmInputManager::isMiddleMouseDown() const
    {
        return SDL_BUTTON(SDL_BUTTON_MIDDLE);
    }
}
