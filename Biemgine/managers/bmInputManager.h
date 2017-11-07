#pragma once

namespace biemgine {
    class bmInputManager
    {
    public:
        bmInputManager();

        void update();
        bool isKeyDown(const char* key);
        bool isKeyDown(const SDL_Scancode key);
    private:
        const Uint8* keyStates;
    };
}
